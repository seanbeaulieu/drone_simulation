#ifndef HELI_FACTORY_H_
#define HELI_FACTORY_H_

#include <vector>

#include "Helicopter.h"
#include "IEntity.h"
#include "IEntityFactory.h"
/**
 * @brief Creates a new Helicopter object if the text in the provided JsonObject
 *parameter is “helicopter”
 *
 * @param entity, a memory address for a JsonObject
 * @return Helicopter, a new Helicopter object filled with information from
 *entity parameter
 **/
class HelicopterFactory : public IEntityFactory {
 public:
  virtual ~HelicopterFactory() {}
  IEntity* CreateEntity(JsonObject& entity);
};

#endif