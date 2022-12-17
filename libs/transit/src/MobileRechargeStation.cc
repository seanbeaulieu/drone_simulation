#include "MobileRechargeStation.h"

MobileRechargeStation ::MobileRechargeStation(JsonObject& obj)
    : RechargeStation(obj) {
  JsonArray pos(obj["position"]);
  position = {pos[0], pos[1], pos[2]};

  JsonArray dir(obj["direction"]);
  direction = {dir[0], dir[1], dir[2]};

  speed = obj["speed"];

  available = true;
}

MobileRechargeStation ::~MobileRechargeStation() {}

void MobileRechargeStation ::SetStrategyName(std::string strategyName) {
  // fixme later need startey name???
  return;
}

void MobileRechargeStation ::SetStrategy(IStrategy* strategy) {
  if (this->strategy) {
    delete this->strategy;
  }
  this->strategy = strategy;
  return;
}

void MobileRechargeStation::Update(double dt, std::vector<IEntity*> scheduler) {
  if (strategy) {  // moving
    strategy->Move(this, dt);
    if (strategy->IsCompleted()) {
      delete strategy;
      strategy = NULL;
    }
  } else {
    Vector3 random;
    float x = -1400 + static_cast<float>(rand()) *
                          static_cast<float>(1500 - -1400) / RAND_MAX;
    float y = 300;  // + static_cast<float>(rand()) * static_cast<float>(1000 -
                    // 240) / RAND_MAX;
    float z = -800 + static_cast<float>(rand()) *
                         static_cast<float>(800 - -800) / RAND_MAX;
    random.x = x;
    random.y = y;
    random.z = z;
    SetDestination(random);
    SetStrategy(new BeelineStrategy(this->position, this->destination));
  }

  for (int i = 0; i < recharging.size();
       i++) {  // move and recharge carried batteries
    recharging[i]->SetPosition(this->position);
    recharging[i]->SetDirection(this->direction);
    recharging[i]->Recharge(dt * 2);
    if (!(recharging[i]->GetCharging())) {  // remove if done
      recharging.erase(recharging.begin() + i);
      i--;  // since this shrinks the vector
    }
  }
}

void MobileRechargeStation::Rotate(double angle) {
  Vector3 dirTmp = direction;
  direction.x = dirTmp.x * std::cos(angle) - dirTmp.z * std::sin(angle);
  direction.z = dirTmp.x * std::sin(angle) + dirTmp.z * std::cos(angle);
}
