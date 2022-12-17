#include "EmergencyPickup.h"

EmergencyPickup ::EmergencyPickup(JsonObject& obj) : details(obj) {
  JsonArray pos(obj["position"]);
  position = {pos[0], pos[1], pos[2]};

  JsonArray dir(obj["direction"]);
  direction = {dir[0], dir[1], dir[2]};

  speed = obj["speed"];

  available = true;
}

EmergencyPickup ::~EmergencyPickup() {}

void EmergencyPickup ::SearchDrone() {
  if (entities == NULL) {
    droneBattery = NULL;
    return;
  }
  for (IEntity* temp : (*entities)) {
    JsonObject detailsTemp = temp->GetDetails();
    std::string typeTemp = detailsTemp["type"];
    if (typeTemp.compare("drone") == 0) {
      if (temp->GetEmergency()) {
        droneBattery = temp;
        break;
      }
    }
  }
}

void EmergencyPickup ::Update(double dt, std::vector<IEntity*> scheduler) {
  if (available) {
    this->SearchDrone();
    if (droneBattery) {
      std::cout << "Emergency spotted, pickup on its way" << std::endl;
      // found dead battery
      available = false;
      destination = droneBattery->GetPosition();
      toTargetPosStrategy =
          new BeelineStrategy(this->position, this->destination);
      droneBattery->SetEmergency(false);
    }
  }
  // pathing to drone
  if (toTargetPosStrategy) {
    toTargetPosStrategy->Move(this, dt);
    if (toTargetPosStrategy->IsCompleted()) {
      // pick up drone and start path to station
      delete toTargetPosStrategy;
      toTargetPosStrategy = NULL;
      IEntity* nearTemp = droneBattery->GetNearestRecharge(*entities);
      if (nearTemp) {
        destination = nearTemp->GetPosition();
        toTargetDestStrategy = new BeelineStrategy(this->position, destination);
      }
    }
  }
  // carrying drone to station
  else if (toTargetDestStrategy) {
    // recalc in case of mobile station
    delete toTargetDestStrategy;
    IEntity* nearTemp = droneBattery->GetNearestRecharge(*entities);
    if (nearTemp) {
      destination = nearTemp->GetPosition();
      toTargetDestStrategy =
          new BeelineStrategy(this->position, this->destination);
      // move and carry drone
      toTargetDestStrategy->Move(this, dt);
      droneBattery->SetPosition(this->position);
      droneBattery->SetDirection(this->direction);
      if (toTargetDestStrategy->IsCompleted()) {
        nearTemp->AddBattery(droneBattery);
        delete toTargetDestStrategy;
        toTargetDestStrategy = NULL;
        available = true;
        droneBattery = NULL;
      }
    }
  }
}

void EmergencyPickup::Rotate(double angle) {
  Vector3 dirTmp = direction;
  direction.x = dirTmp.x * std::cos(angle) - dirTmp.z * std::sin(angle);
  direction.z = dirTmp.x * std::sin(angle) + dirTmp.z * std::cos(angle);
}
