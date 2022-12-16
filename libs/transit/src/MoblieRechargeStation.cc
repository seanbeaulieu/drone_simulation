#include "MobileRechargeStation.h"


MobileRechargeStation :: MobileRechargeStation(JsonObject &obj) : RechargeStation(obj){
    JsonArray pos(obj["position"]);
    position = {pos[0], pos[1], pos[2]};

    JsonArray dir(obj["direction"]);
    direction = {dir[0], dir[1], dir[2]};

    speed = obj["speed"];

    available = true;
}

MobileRechargeStation :: ~MobileRechargeStation() {}

void MobileRechargeStation :: SetStrategyName(std::string strategyName){
    //fixme later need startey name???
    return;
}

void MobileRechargeStation :: SetStrategy(IStrategy* strategy){
    //FIXME later
    this->strategy = strategy;
    return;
}

void MobileRechargeStation:: Update(double dt, std::vector<IEntity*> scheduler){
    //FIXME:why is this not moving?
    if (strategy) {
      strategy->Move(this, dt);
    if (strategy->IsCompleted()) {
      delete strategy;
      strategy = NULL;
    }
  } else {
    Vector3 random;
    //double angle = dt * 2 * pi / period;
    float x = -1400 + static_cast<float>(rand()) *
                          static_cast<float>(1500 - -1400) / RAND_MAX;
    float y = 300;
    float z = -800 + static_cast<float>(rand()) *
                         static_cast<float>(800 - -800) / RAND_MAX;
    random.x = x;
    random.y = y;
    random.z = z;
    SetDestination(random);
    SetStrategy(new BeelineStrategy(this->position, this->destination));
  }
}


void MobileRechargeStation::Rotate(double angle) {
  Vector3 dirTmp = direction;
  direction.x = dirTmp.x * std::cos(angle) - dirTmp.z * std::sin(angle);
  direction.z = dirTmp.x * std::sin(angle) + dirTmp.z * std::cos(angle);
}