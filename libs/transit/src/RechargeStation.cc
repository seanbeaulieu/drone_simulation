#include "RechargeStation.h"

RechargeStation :: RechargeStation(JsonObject &obj) : details(obj){
    JsonArray pos(obj["position"]);
    position = {pos[0], pos[1], pos[2]};

    JsonArray dir(obj["direction"]);
    direction = {dir[0], dir[1], dir[2]};

    speed = obj["speed"];
    available = true;
}


JsonObject RechargeStation::GetDetails() const { return details; }



void RechargeStation :: Update(double dt, std::vector<IEntity*> scheduler){
    for(int i = 0; i<recharging.size(); i++){
        // check if the drone need to charge, make sure that drone before it reach the recharge station, set the charging to false.
        if(recharging[i]->GetCharging())
        {
            recharging.erase(recharging.begin() + i);
        }
        else{
            recharging[i]->Recharge(dt*2);
        }
    }
}

void RechargeStation::SetAvailability(bool choice) { available = choice; }