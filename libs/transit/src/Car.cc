#include "Car.h"

#include "AstarStrategy.h"

Car::Car(JsonObject& obj) : details(obj) {
  JsonArray pos(obj["position"]);
  position = {pos[0], pos[1], pos[2]};

  JsonArray dir(obj["direction"]);
  direction = {dir[0], dir[1], dir[2]};

  speed = obj["speed"];
}

Car::~Car() {}

void Car::Update(double dt, std::vector<IEntity*> scheduler) {
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
    float y = 240 + static_cast<float>(rand()) * static_cast<float>(280 - 240) /
                        RAND_MAX;
    float z = -800 + static_cast<float>(rand()) *
                         static_cast<float>(800 - -800) / RAND_MAX;
    random.x = x;
    random.y = y;
    random.z = z;
    SetDestination(random);
    strategy = new AstarStrategy(position, destination, graph);
  }
}

void Car::SetPosition(Vector3 pos_) { position = pos_; }
void Car::SetDirection(Vector3 dir_) { direction = dir_; }
void Car::SetDestination(Vector3 des_) { destination = des_; }
Vector3 Car::GetPosition() const { return position; }
Vector3 Car::GetDirection() const { return direction; }
Vector3 Car::GetDestination() const { return destination; }
JsonObject Car::GetDetails() const { return details; }
float Car::GetSpeed() const { return speed; }
