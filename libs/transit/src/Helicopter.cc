#include "Helicopter.h"

#include "BeelineStrategy.h"
Helicopter::Helicopter(JsonObject& obj) : details(obj) {
  JsonArray pos(obj["position"]);
  position = {pos[0], pos[1], pos[2]};

  JsonArray dir(obj["direction"]);
  direction = {dir[0], dir[1], dir[2]};

  speed = obj["speed"];
  available = true;
}

Helicopter::~Helicopter() {
  // Delete dynamically allocated variables
}

void Helicopter::Update(double dt, std::vector<IEntity*> scheduler) {
  if (strategy) {
    strategy->Move(this, dt);
    if (strategy->IsCompleted()) {
      delete strategy;
      strategy = NULL;
    }
  } else {
    Vector3 random;
    float x = -1400 + static_cast<float>(rand()) *
                          static_cast<float>(1500 - -1400) / RAND_MAX;
    float y = 240 + static_cast<float>(rand()) *
                        static_cast<float>(1000 - 240) / RAND_MAX;
    float z = -800 + static_cast<float>(rand()) *
                         static_cast<float>(800 - -800) / RAND_MAX;
    random.x = x;
    random.y = y;
    random.z = z;
    SetDestination(random);
    strategy = new BeelineStrategy(this->position, this->destination);
  }
}

void Helicopter::Rotate(double angle) {
  Vector3 dirTmp = direction;
  direction.x = dirTmp.x * std::cos(angle) - dirTmp.z * std::sin(angle);
  direction.z = dirTmp.x * std::sin(angle) + dirTmp.z * std::cos(angle);
}
