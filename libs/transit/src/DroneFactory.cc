#include "DroneFactory.h"

IEntity* DroneFactory::CreateEntity(JsonObject& entity) {
  std::string type = entity["type"];
  if (type.compare("drone") == 0) {
    std::cout << "Drone Created" << std::endl;
    BatteryDecorator* dr = new BatteryDecorator(entity);
    return dr;
    // return new Drone(entity); // pre-hw4 call
  }
  return nullptr;
}
