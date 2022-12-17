#ifndef RST_H_
#define RST_H_

#include "IEntity.h"
#include "IEntityFactory.h"
#include "RechargeStation.h"

/**
 * @brief Recharge Station Factory class to build new RechargeStations
 **/
class RechargeStationFactory : public IEntityFactory {
 public:
  virtual ~RechargeStationFactory() {}

  /**
   * @brief Creates a new Recharge Station
   *
   * @param entity, a memory address for a JsonObject
   * @return a pointer to the newly created Recharge Station
   **/
  IEntity* CreateEntity(JsonObject& entity);
};

#endif