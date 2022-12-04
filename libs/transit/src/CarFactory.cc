#include "CarFactory.h"

IEntity* CarFactory::CreateEntity(JsonObject& entity) {
  std::string type = entity["type"];
  if (type.compare("car") == 0) {
    std::cout << "Car Created" << std::endl;
    return new Car(entity);
  }
  return nullptr;
}
