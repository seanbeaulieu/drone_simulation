#include "BatteryDecorator.h"

BatteryDecorator :: BatteryDecorator(Drone* drone) {
 this->charge = 100;
 this->drone = drone;
}

BatteryDecorator :: BatteryDecorator(JsonObject& obj) {
	charge = 100;
	drone = new Drone(obj);
}

BatteryDecorator :: ~BatteryDecorator(){
    if (drone) {
		delete drone;
	}
}

//don't need it, maybe
// void BatteryDecorator::SetDrone(Drone* drone){

// }

void BatteryDecorator::GetNearestEntity(std::vector<IEntity*> scheduler){
    drone->GetNearestEntity(scheduler);
}

void BatteryDecorator::Update(double dt, std::vector<IEntity*> scheduler){
//FIXME: not working right now with drone factory.
    drone->Update(dt, scheduler);
} 
