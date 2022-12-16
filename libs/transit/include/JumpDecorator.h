#ifndef JUMP_DECORATOR_H_
#define JUMP_DECORATOR_H_

#include <vector>

#include "CelebrationDecorator.h"
#include "IStrategy.h"

class JumpDecorator : public CelebrationDecorator {
 public:
  JumpDecorator(IStrategy* strategy_) : CelebrationDecorator(strategy_) {}

  /**
     * @brief Checks to see if the route is completed and does a jump celebration
     * 
     * @return IsCompleted, a true or false boolean value
     **/
  bool IsCompleted();

  /**
    * @brief Moves the entity
    * 
    * @param entity, a pointer to an IEntity object to be moved
    * @param dt, a double value to be moved by
    * @return None
    **/
  void Move(IEntity* entity, double dt);
};  // close class

#endif  // JUMP_DECORATOR_H_