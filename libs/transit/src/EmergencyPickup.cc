#include "EmergencyPickup.h"

EmergencyPickup :: EmergencyPickup(JsonObject &obj) : details(obj){
    JsonArray pos(obj["position"]);
    position = {pos[0], pos[1], pos[2]};

    JsonArray dir(obj["direction"]);
    direction = {dir[0], dir[1], dir[2]};

    speed = obj["speed"];

    available = true;
}

EmergencyPickup :: ~EmergencyPickup(){}




void EmergencyPickup :: Update(double dt, std::vector<IEntity*> scheduler){
    //FIXME:

    if(strategy){
      strategy->Move(this, dt);

      if(strategy->IsCompleted()){
        delete strategy;
        strategy = NULL;
      }  
    }
    else{
        //FIXME:check if it need to pick up the drone
        if(false){
            destination = droneBattery->GetDestination();
            strategy = new BeelineStrategy(this->position, this->destination);
        }
    }

        
}

