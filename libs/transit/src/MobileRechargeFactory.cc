#include "MobileRechargeFactory.h"

IEntity* MobileRechargeFactory::CreateEntity(JsonObject& entity) {
  std::string type = entity["type"];
  if (type.compare("mobilerecharge") == 0) {
    std::cout << "MobileRecharge Created" << std::endl;
    return new MobileRechargeStation(entity);
  }
  return nullptr;
}
