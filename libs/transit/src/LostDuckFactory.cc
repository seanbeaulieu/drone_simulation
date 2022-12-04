#include "LostDuckFactory.h"

IEntity* LostDuckFactory::CreateEntity(JsonObject& entity) {
  std::string type = entity["type"];
  if (type.compare("lostduck") == 0) {
    std::cout << "Lost Duck Created" << std::endl;
    return new Lost_Duck(entity);
  }
  return nullptr;
}
