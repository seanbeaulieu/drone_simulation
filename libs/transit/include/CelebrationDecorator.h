#ifndef CELEBRATION_DECORATOR_H_
#define CELEBRATION_DECORATOR_H_

#include <vector>

#include "IStrategy.h"

/**
 * @brief Celebration Decorator for the IStrategy.
 **/

class CelebrationDecorator : public IStrategy {
 public:
  CelebrationDecorator(IStrategy *strategy_) {
    strategy = strategy_;
    time = 0;
  }
  void Move(IEntity *entity, double dt);

  /**
   * @brief Checks to see if the route is completed and does a celebration if so
   * @return IsCompleted, a true or false boolean value
   **/
  bool IsCompleted();

 protected:
  IStrategy *strategy;
  float time;
};  // close class

#endif  // CELEBRATION_DECORATOR_H_