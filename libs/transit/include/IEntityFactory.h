#ifndef I_ENTITY_FACTORY_H_
#define I_ENTITY_FACTORY_H_

#include "Drone.h"
#include "IEntity.h"
#include "IEntityFactory.h"
#include "util/json.h"

/**
 * @brief IEntityFactory class to make new IEntitys
 * @param entity, a memory address for a JsonObject
 **/
class IEntityFactory {
 public:
  virtual ~IEntityFactory() {}

  /**
   * @brief Creates a new IEntity object
   *
   * @param entity, a memory address for a JsonObject
   * @return a pointer to the IEntity that was created
   **/
  virtual IEntity* CreateEntity(JsonObject& entity) = 0;
};

#endif