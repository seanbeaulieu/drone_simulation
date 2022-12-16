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
	if (entities == NULL) { // no entities = no stations
		nearestRecharge = NULL;
		return NULL;
	}
	if (nearestRecharge) { // in case all recharge stations get removed
		delete nearestRecharge;
		nearestRecharge = NULL;
	}
	double minDist = -1;
	for (IEntity* entity : search) {
		std::string type = (entity->GetDetails())["type"]; // type check
		if (type.compare("rechargestation") == 0 || type.compare("moblierechargestation") == 0) {
			double curDist = entity->GetPosition().Distance(GetPosition());
			if (curDist < minDist || minDist == -1) { // distance check
				minDist = curDist;
				if (nearestRecharge) { // prevent leaks
					delete nearestRecharge;
					nearestRecharge = entity;
				}
			}
		}
	}
	if (nearestRecharge) { // if successful
		rechargeDest = nearestRecharge->GetPosition();
		nearIsMobile = true; // more efficient to assume true at first
	}
	return nearestRecharge;
}

double BatteryDecorator::TripDistance(IEntity* passenger) {
	double totalDist = 0;
	totalDist += this->GetPosition().Distance(this->GetDestination());
	totalDist += this->GetDestination().Distance(passenger->GetDestination());
	totalDist += passenger->GetDestination().Distance(nearestRecharge->GetPosition());
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
	
	if (charge <= 0 || charging) { // dead or charging, do nothing
		return;
	}
	
	if (nearestRecharge == NULL) {
		GetNearestRecharge(*entities);
		//std::cout<<"good GetNearestRecharge"<<std::endl;
	}
	
	if (this->GetAvailability()) { // no target, no moving
		drone->Update(dt, scheduler); // try to initialize drone route
		if (!(this->GetAvailability())) { // if successful (results in 1 move)
			charge -= dt; // only drain when moving
			if (nearestRecharge) { // if no recharge stations, attempt trip anyways
				IEntity* passenger = drone->ReturnNearestEntity();
				double dist = TripDistance(passenger);
				if ((dist / this->GetSpeed()) > (charge)) { // trip too long for battery
					passenger->SetAvailability(true);
					rechargeDest = nearestRecharge->GetPosition();
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
			// nearestRecharge->addBattery(this); // TODO
			charging = true;
			nearIsMobile = true;
		}
	}
	else { // proceed trip as normal
		drone->Update(dt, scheduler);
		charge -= dt;
		if (this->GetAvailability()) {
			GetNearestRecharge(*entities);
		}
	}
}

void BatteryDecorator::Recharge(double amount) {
	charge += amount;
	if (charge >= 100) {
		charge = 100;
		charging = false;
		this->SetAvailability(true);
	}
}
	
