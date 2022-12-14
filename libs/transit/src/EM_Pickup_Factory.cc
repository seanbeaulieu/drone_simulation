#include "EM_Pickup_Factory.h"

IEntity* EM_Pickup_Factory::CreateEntity(JsonObject& entity) {
  std::string type = entity["type"];
  if (type.compare("emergencypickup") == 0) {
    std::cout << "EmergencyPickup Created" << std::endl;
    return new EmergencyPickup(entity);
  }
  return nullptr;
}