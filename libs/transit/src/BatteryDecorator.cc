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

//don't need it, maybe
// void BatteryDecorator::SetDrone(Drone* drone){

// }

void BatteryDecorator::GetNearestEntity(std::vector<IEntity*> scheduler){
    drone->GetNearestEntity(scheduler);
}

void BatteryDecorator::Update(double dt, std::vector<IEntity*> scheduler){
//FIXME: not working right now with drone factory.
    position = this->GetPosition();
    if (charge > 0){
       drone->Update(dt, scheduler); 
    }
    if(this->GetPosition().Distance(position) > 0.001){
       charge -= dt;
       std::cout<<"charge is: "<<charge<<std::endl; 
    }
} 
