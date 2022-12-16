#ifndef Emergency_P_F_H_
#define Emergency_P_F_H_

#include "IEntity.h"
#include "IEntityFactory.h"
#include "EmergencyPickup.h"
#include "BatteryDecorator.h"

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