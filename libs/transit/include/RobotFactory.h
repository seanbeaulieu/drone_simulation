#ifndef ROBOT_FACTORY_H_
#define ROBOT_FACTORY_H_

#include "IEntity.h"
#include "IEntityFactory.h"
#include "Robot.h"

#include <vector>

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