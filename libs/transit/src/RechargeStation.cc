#include "RechargeStation.h"

RechargeStation ::RechargeStation(JsonObject& obj) : details(obj) {
  JsonArray pos(obj["position"]);
  position = {pos[0], pos[1], pos[2]};

  JsonArray dir(obj["direction"]);
  direction = {dir[0], dir[1], dir[2]};

  speed = obj["speed"];
  available = true;
}

JsonObject RechargeStation::GetDetails() const { return details; }

void RechargeStation ::Update(double dt, std::vector<IEntity*> scheduler) {
  for (int i = 0; i < recharging.size(); i++) {  // recharge carried batteries
    recharging[i]->Recharge(dt * 3);
    if (!(recharging[i]->GetCharging())) {  // remove if done
      recharging.erase(recharging.begin() + i);
      i--;  // since this shrinks the vector, need to check same index
    }
  }
}

void RechargeStation ::AddBattery(IEntity* battery) {
  BatteryDecorator* temp = static_cast<BatteryDecorator*>(battery);
  temp->SetCharging(true);
  recharging.push_back(temp);
}

void RechargeStation::SetAvailability(bool choice) { available = choice; }
