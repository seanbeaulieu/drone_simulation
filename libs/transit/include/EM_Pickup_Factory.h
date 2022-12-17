#ifndef Emergency_P_F_H_
#define Emergency_P_F_H_

#include "BatteryDecorator.h"
#include "EmergencyPickup.h"
#include "IEntity.h"
#include "IEntityFactory.h"

/**
 * @brief Creates a New EmergencyPickup Entity object if the text in provided
 *JsonObject parameter is "EmergencyPickup"
 **/

class EM_Pickup_Factory : public IEntityFactory {
 public:
  virtual ~EM_Pickup_Factory() {}

  /**
   * @brief Creates a new entity as an Emergency Pickup Drone
   *
   * @param entity, a memory address to a JsonObject
   * @return a pointer to the newly created Emergency Pickup Drone
   **/
  IEntity* CreateEntity(JsonObject& entity);
};

#endif