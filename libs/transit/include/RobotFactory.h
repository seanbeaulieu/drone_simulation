#ifndef ROBOT_FACTORY_H_
#define ROBOT_FACTORY_H_

#include <vector>

#include "IEntity.h"
#include "IEntityFactory.h"
#include "Robot.h"

/**
 * @brief Robot Factory class that creates Robot class if the provided text
 * is "robot"
 * @param entity, a memory address for a JsonObject
 *
 * @return A new Robot filled with information from entity
 **/
class RobotFactory : public IEntityFactory {
 public:
  /**
   * @brief Creates a new Robot entity
   *
   * @param entity, a memory address to a JsonObject
   * @return a pointer to the newly created Robot
   **/
  IEntity* CreateEntity(JsonObject& entity);
};

#endif