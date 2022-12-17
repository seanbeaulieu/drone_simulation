#include "BatteryDecorator.h"

BatteryDecorator ::BatteryDecorator(Drone* drone) { this->drone = drone; }

BatteryDecorator ::BatteryDecorator(JsonObject& obj) { drone = new Drone(obj); }

BatteryDecorator ::~BatteryDecorator() {
  if (drone) {
    delete drone;
  }
}

IEntity* BatteryDecorator::GetNearestRecharge(std::vector<IEntity*> search) {
  // reset in case stations are removed
  nearestRecharge = NULL;
  // no entities = no stations
  if (entities == NULL) {
    return NULL;
  }
  double minDist = -1;
  for (IEntity* entity : search) {
    std::string type = (entity->GetDetails())["type"];
    // type check
    if (type.compare("rechargestation") == 0 ||
        type.compare("mobilerecharge") == 0) {
      double curDist = entity->GetPosition().Distance(this->GetPosition());
      // distance check
      if (curDist < minDist || minDist == -1) {
        minDist = curDist;
        nearestRecharge = entity;
      }
    }
  }
  // if successful
  if (nearestRecharge) {
    rechargeDest = nearestRecharge->GetPosition();
    // more efficient to assume true at first
    nearIsMobile = true;
  }
  return nearestRecharge;
}

IEntity* BatteryDecorator::GetNearestRecharge(std::vector<IEntity*> search,
                                              Vector3 pos) {
  if (entities == NULL) {
    return NULL;
  }
  IEntity* temp = NULL;
  double minDist = -1;
  for (IEntity* entity : search) {
    std::string type = (entity->GetDetails())["type"];
    // type check
    if (type.compare("rechargestation") == 0 ||
        type.compare("mobilerecharge") == 0) {
      double curDist = entity->GetPosition().Distance(pos);
      // distance check
      if (curDist < minDist || minDist == -1) {
        minDist = curDist;
        temp = entity;
      }
    }
  }
  return temp;
}

double BatteryDecorator::TripDistance(IEntity* passenger) {
  double totalDist = 0;
  if (passenger == NULL) {
    return 0;
  }
  if (passenger->GetPosition().Distance(passenger->GetDestination()) < 1.0) {
    return 0;
  }
  IEntity* temp = GetNearestRecharge(*entities, passenger->GetDestination());
  // drone to passenger
  totalDist += this->GetPosition().Distance(passenger->GetPosition());
  // passenger to destination
  totalDist += passenger->GetPosition().Distance(passenger->GetDestination());
  // destination to recharge (nearest to destination)
  totalDist += passenger->GetDestination().Distance(temp->GetPosition());
  // should roughly account for non-beeline pathing, worst case is
  // it overcorrects and drone takes the safer, recharge choice
  totalDist *= sqrt(2);
  return totalDist;
}

void BatteryDecorator::GetNearestEntity(std::vector<IEntity*> scheduler) {
  drone->GetNearestEntity(scheduler);
}

void BatteryDecorator::Update(double dt, std::vector<IEntity*> scheduler) {
  // current implementation allows battery failure from:
  // 1. pathing to the mobile recharge station
  // 2. making battery too small to cover any trip from full capacity
  // which is both less difficult on us and can actually showcase the pickup

  // do nothing.
  // can kinda break if charge somehow hits exactly 0 on its own.
  // tried to fix but multithreading (i think) breaks it
  // by simultaneously reading/writing states
  if (charging || emergency || charge == 0) {
    return;
  }
  // dead
  if (charge < 0) {
    charge = 0;
    emergency = true;
    std::cout << "emergency! drone died." << std::endl;
    return;
  }

  // 1 of 3. pathing to recharge
  if (rechargeStrategy) {
    // initally assumed mobile, so always run at least once
    if (nearIsMobile) {
      if ((nearestRecharge->GetPosition() - rechargeDest).Magnitude() <= 1.0) {
        // if nearest doesn't move, note as such to skip redundant computation
        nearIsMobile = false;
      }
      rechargeDest = nearestRecharge->GetPosition();
      delete rechargeStrategy;
      rechargeStrategy = new BeelineStrategy(this->GetPosition(), rechargeDest);
    }
    rechargeStrategy->Move(this, dt);
    charge -= dt;
    // reached recharge, start charging
    if (rechargeStrategy->IsCompleted()) {
      delete rechargeStrategy;
      rechargeStrategy = NULL;
      // note: sets charging to true
      nearestRecharge->AddBattery(this);
    }
  }
  // 2 of 3. no route
  else if (this->GetAvailability()) {
    // try to initialize drone route
    drone->Update(dt, scheduler);
    // if successful routing (results in 1 move)
    if (!(this->GetAvailability())) {
      charge -= dt;
      // only look for path to station if they exist
      if (GetNearestRecharge(*entities)) {
        IEntity* temp = drone->ReturnNearestEntity();
        double dist = TripDistance(temp);
        // if full trip too long for battery
        if ((dist / this->GetSpeed()) > charge) {
          temp = GetNearestRecharge(*entities, temp->GetPosition());
          dist = temp->GetPosition().Distance(this->GetPosition()) * sqrt(2);
          // if it can make it to the "better" station, do so
          if ((dist / this->GetSpeed()) < charge) {
            rechargeDest = temp->GetPosition();
          } else {
            rechargeDest = nearestRecharge->GetPosition();
          }
          rechargeStrategy =
              new BeelineStrategy(this->GetPosition(), rechargeDest);
        }
      }
    }
    // if unsuccessful routing and low battery, recharge
    else if (charge / MAX_CHARGE < 0.5) {
      if (GetNearestRecharge(*entities)) {
        rechargeDest = nearestRecharge->GetPosition();
        rechargeStrategy =
            new BeelineStrategy(this->GetPosition(), rechargeDest);
      }
    }
  }
  // 3 of 3. proceed trip as normal
  else {
    drone->Update(dt, scheduler);
    charge -= dt;
    if (this->GetAvailability()) {
      std::cout << "trip finished." << std::endl;
      nearestRecharge = NULL;
    }
  }
}

void BatteryDecorator::Recharge(double amount) {
  charge += amount;
  if (charge >= MAX_CHARGE) {
    std::cout << "done charging." << std::endl;
    charge = MAX_CHARGE;
    charging = false;
    emergency = false;
  }
}
