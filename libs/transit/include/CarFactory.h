#ifndef CAR_FACTORY_H_
#define CAR_FACTORY_H_

#include <vector>

#include "Car.h"
#include "IEntity.h"
#include "IEntityFactory.h"

/**
 * @brief Creates a new Car object if the text in the provided JsonObject
 *parameter is “car”
 *
 * @param entity, a memory address for a JsonObject
 * @return Car, a new Car object filled with information from entity parameter
 **/
class CarFactory : public IEntityFactory {
 public:
  virtual ~CarFactory() {}
  IEntity* CreateEntity(JsonObject& entity);
};

#endif