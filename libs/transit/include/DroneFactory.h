#ifndef DRONE_FACTORY_H_
#define DRONE_FACTORY_H_

#include <vector>

#include "BatteryDecorator.h"
#include "Drone.h"
#include "IEntity.h"
#include "IEntityFactory.h"
/**
 * @brief drone factory.
 */
class DroneFactory : public IEntityFactory {
 public:
  virtual ~DroneFactory() {}

  /**
   * @brief Creates a new entity as a Drone
   *
   * @param entity, a memory address to a JsonObject
   * @return A pointer to the createdEntity
   **/
  IEntity* CreateEntity(JsonObject& entity);
};

#endif