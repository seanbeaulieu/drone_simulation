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
			double curDist = entity->GetPosition().Distance(GetPosition());
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

double BatteryDecorator::TripDistance(IEntity* passenger) {
	double totalDist = 0;
	totalDist += this->GetPosition().Distance(this->GetDestination());
	totalDist += this->GetDestination().Distance(passenger->GetDestination());
	totalDist += passenger->GetDestination().Distance(nearestRecharge->GetPosition());
	return totalDist * sqrt(2);
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
	if(charge > 30){
		drone->SetAvailability(false);
		if(drone->GetPosition().Distance(rechargeDest) < 1){
			charging = true;
			Recharge(dt);
		}
		else{
			nearestRecharge = GetNearestRecharge(*entities);
			rechargeDest = nearestRecharge->GetPosition();
			drone->SetDestination(rechargeDest);
			position = drone->GetPosition();
			drone->Update(dt,scheduler);
			if(drone->GetPosition().Distance(position) > 0.1){
				charge -= dt;
				std::cout<<"charge: "<<charge<<std::endl;
			}
		}
	}
	else if(charge <= 0){
		
	}
	else{
		position = drone->GetPosition();
		drone->Update(dt,scheduler);
		if(drone->GetPosition().Distance(position) > 0.1){
			charge -= dt;
			std::cout<<"charge: "<<charge<<std::endl;
		}
	}
	
	
	
}

void BatteryDecorator::Recharge(double amount) {
	charge += amount;
	if (charge >= 100) {
		std::cout << "done charging!" << std::endl;
		charge = 100;
		charging = false;
		this->SetAvailability(true);
	}
}
	
