#include "Lost_Duck.h"

Lost_Duck::Lost_Duck(JsonObject& obj) : details(obj) {
  JsonArray pos(obj["position"]);
  position = {pos[0], pos[1], pos[2]};

  JsonArray dir(obj["direction"]);
  direction = {dir[0], dir[1], dir[2]};

  speed = obj["speed"];
  available = true;
  time = 0.0;
}

Lost_Duck::~Lost_Duck() {
  // Delete dynamically allocated variables
}

void Lost_Duck::Update(double dt, std::vector<IEntity*> scheduler) {
  if (strategy) {
    if (rand() % 10000 == 0) {
      if (strat2) {
        delete strat2;
        strat2 = NULL;
      }
      Vector3 random;
      float x = 50 - (rand() % 100);
      float y = 0;
      float z = 50 - (rand() % 100);
      random.x = x;
      random.y = y;
      random.z = z;
      strat2 = new DijkstraStrategy(position, (position + random), graph);
    }
    if (strat2) {
      if (!strat2->IsCompleted()) {
        strat2->Move(this, dt);
      } else {
        strategy->Move(this, dt);
        if (strategy->IsCompleted()) {
          delete strategy;
          strategy = NULL;
        }
      }
    } else {
      strategy->Move(this, dt);
      if (strategy->IsCompleted()) {
        std::cout << "strategy complete, deleting \n";  // t
        delete strategy;
        strategy = NULL;
      }
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
    strategy = new DijkstraStrategy(position, destination, graph);
  }
}

void Lost_Duck::Rotate(double angle) {
  Vector3 dirTmp = direction;
  direction.x = dirTmp.x * std::cos(angle) - dirTmp.z * std::sin(angle);
  direction.z = dirTmp.x * std::sin(angle) + dirTmp.z * std::cos(angle);
}
