#ifndef LOST_DUCK_FACTORY_H_
#define LOST_DUCK_FACTORY_H_

#include <vector>

#include "IEntity.h"
#include "IEntityFactory.h"
#include "Lost_Duck.h"

/**
 * @brief Creates a new LostDuck object if the text in the provided JsonObject
 *parameter is “LostDuck”
 *
 * @param entity, a memory address for a JsonObject
 * @return Car, a new Car object filled with information from entity parameter
 **/
class LostDuckFactory : public IEntityFactory {
 public:
  virtual ~LostDuckFactory() {}
  IEntity* CreateEntity(JsonObject& entity);
};

#endif
