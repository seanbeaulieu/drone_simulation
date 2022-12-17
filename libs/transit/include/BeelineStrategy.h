#ifndef BEELINE_H_
#define BEELINE_H_

/**
 * include
 */
#include <vector>

#include "IEntity.h"
#include "IStrategy.h"
#include "math/vector3.h"
/**
 * @brief this class inhertis from the IStrategy class and is responsible for
 * generating the beeline that the drone will take.
 */
class BeelineStrategy : public IStrategy {
 public:
  BeelineStrategy(Vector3 position, Vector3 destination);
  ~BeelineStrategy();

  /**
   * @brief Moves the provided entity using the beeline strategy
   *
   * @param entity, a pointer to an IEntity object to be moved
   * @param dt, a double value amount to move
   * @return None
   **/
  void Move(IEntity* entity, double dt);

  /**
   * @brief Checks to see if the route is completed
   *
   * @return IsCompleted, a true or false boolean value
   **/
  bool IsCompleted();

 private:
  Vector3 position;
  Vector3 destination;
};      // end class
#endif  // BEELINE_H_