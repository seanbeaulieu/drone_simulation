#ifndef DRONE_FACTORY_H_
#define DRONE_FACTORY_H_

#include "IEntity.h"
#include "IEntityFactory.h"
#include "Drone.h"
#include "BatteryDecorator.h"
#include <vector>

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