#ifndef SPIN_DECORATOR_H_
#define SPIN_DECORATOR_H_

#include <vector>

#include "CelebrationDecorator.h"
#include "IStrategy.h"

/**
 * @brief The SpinDecorator class. This class applies the spin animation to
 *Celebration
 * @param strategy_, a strategy check that will determine what celebration to
 *use
 **/
class SpinDecorator : public CelebrationDecorator {
 public:
  SpinDecorator(IStrategy* strategy_) : CelebrationDecorator(strategy_) {}

  /**
   * @brief Checks to see if the route is completed and spins if so
   *
   * @return IsCompleted, a boolean true or false value
   **/
  bool IsCompleted();

  /**
   * @brief Moves the provided entity
   *
   * @param entity, a pointer to an IEntity object
   * @param dt, a double value to move by
   * @return None
   **/
  void Move(IEntity* entity, double dt);
};  // close class

#endif  // SPIN_DECORATOR_H_