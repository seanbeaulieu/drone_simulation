#include "BatteryDecorator.h"

BatteryDecorator :: BatteryDecorator(JsonObject& entity) : Drone(entity) {
 this->charge = 100;
 drone = new Drone(entity);
}

BatteryDecorator :: ~BatteryDecorator(){
    delete drone;
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