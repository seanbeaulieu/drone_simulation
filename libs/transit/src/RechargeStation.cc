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

void RechargeStation::SetAvailability(bool choice) { available = choice; }