#include "RechargeStationFactory.h"

IEntity* RechargeStationFactory::CreateEntity(JsonObject& entity) {
  std::string type = entity["type"];
  if (type.compare("rechargestation") == 0) {
    std::cout << "RechargeStation Created" << std::endl;
    return new RechargeStation(entity);
  }
  return nullptr;
}