#include "BatteryDecorator.h"

BatteryDecorator :: BatteryDecorator(Drone* drone) {
	this->drone = drone;
}

BatteryDecorator :: BatteryDecorator(JsonObject& obj) {
	drone = new Drone(obj);
}

BatteryDecorator :: ~BatteryDecorator(){
    if (drone) {
		delete drone;
	}
}

IEntity* BatteryDecorator::GetNearestRecharge(std::vector<IEntity*> search) {
	nearestRecharge = NULL; // reset in case stations are removed
	if (entities == NULL) { // no entities = no stations
		return NULL;
	}
	double minDist = -1;
	for (IEntity* entity : search) {
		std::string type = (entity->GetDetails())["type"]; // type check
		if (type.compare("rechargestation") == 0 || type.compare("moblierechargestation") == 0) {
			double curDist = entity->GetPosition().Distance(this->GetPosition());
			if (curDist < minDist || minDist == -1) { // distance check
				minDist = curDist;
				nearestRecharge = entity;
			}
		}
	}
	if (nearestRecharge) { // if successful
		rechargeDest = nearestRecharge->GetPosition();
		nearIsMobile = true; // more efficient to assume true at first
	}
	return nearestRecharge;
}

IEntity* BatteryDecorator::GetNearestRecharge(std::vector<IEntity*> search, Vector3 pos) {
	if (entities == NULL) {
		return NULL;
	}
	IEntity* temp = NULL;
	double minDist = -1;
	for (IEntity* entity : search) {
		std::string type = (entity->GetDetails())["type"]; // type check
		if (type.compare("rechargestation") == 0 || type.compare("moblierechargestation") == 0) {
			double curDist = entity->GetPosition().Distance(pos);
			if (curDist < minDist || minDist == -1) { // distance check
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
	totalDist += this->GetPosition().Distance(passenger->GetPosition()); // drone to passenger
	totalDist += passenger->GetPosition().Distance(passenger->GetDestination()); // passenger to destination
	totalDist += passenger->GetDestination().Distance(temp->GetPosition()); // destination to recharge (nearest to destination)
	totalDist *= sqrt(2); // should roughly account for non-beeline pathing
	return totalDist;
}

void BatteryDecorator::GetNearestEntity(std::vector<IEntity*> scheduler){
    drone->GetNearestEntity(scheduler);
}

void BatteryDecorator::Update(double dt, std::vector<IEntity*> scheduler){
// TODO: Implement logic

// note: may need a way to broadcast a dead battery to emergency pickup?
	
// current implementation allows battery failure due to:
// 1. pathing to the mobile recharge station
// 2. straight-line distance calculation for route length
// which is both less difficult on us and can actually showcase the pickup
	
	if (charging || emergency || charge == 0) { // do nothing
		return;
	}
	if (charge < 0) { // dead
		charge = 0;
		emergency = true;
		std::cout << "emergency! drone died." << std::endl;
		return;
	}
	
	if (this->GetAvailability()) { // no route
		drone->Update(dt, scheduler); // try to initialize drone route
		if (!(this->GetAvailability())) { // if successful (results in 1 move)
			charge -= dt; // only drain when moving
			if (GetNearestRecharge(*entities)) { // only look for path to station if they exist
				IEntity* temp = drone->ReturnNearestEntity();
				double dist = TripDistance(temp);
				if ((dist / this->GetSpeed()) > charge) { // full trip too long for battery
					// temp->SetAvailability(true); // errors
					temp = GetNearestRecharge(*entities, temp->GetPosition());
					dist = temp->GetPosition().Distance(this->GetPosition()) * sqrt(2);
					if ((dist / this->GetSpeed()) < charge) { // if it can make it to the "better" station, do so
						rechargeDest = temp->GetPosition();
					}
					else {
						rechargeDest = nearestRecharge->GetPosition();
					}
					rechargeStrategy = new BeelineStrategy(this->GetPosition(), rechargeDest);
				}
			}
		}
	}
	else if (rechargeStrategy) { // pathing to recharge. deleted and NULL when completed
		if (nearIsMobile) { // initally assumed mobile, so always entered once
			if ((nearestRecharge->GetPosition() - rechargeDest).Magnitude() <= 1.0) {
				nearIsMobile = false;  // if nearest doesn't move, note as such to skip computation
			}
			rechargeDest = nearestRecharge->GetPosition();
			delete rechargeStrategy;
			rechargeStrategy = new BeelineStrategy(this->GetPosition(), rechargeDest);
		}
		rechargeStrategy->Move(this, dt);
		charge -= dt;
		if (rechargeStrategy->IsCompleted()) { // reached recharge, start charging
			delete rechargeStrategy;
			rechargeStrategy = NULL;
			nearestRecharge->AddBattery(this); // sets charging to true
		}
	}
	else { // proceed trip as normal
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
		// this->SetAvailability(true); // results in infinite loop
	}
}
	
