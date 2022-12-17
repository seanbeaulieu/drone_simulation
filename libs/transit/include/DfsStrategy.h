#ifndef DFS_STRATEGY_H_
#define DFS_STRATEGY_H_

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
class DfsStrategy : public IStrategy {
 public:
  DfsStrategy(Vector3 position, Vector3 destination, const IGraph* graph);
  ~DfsStrategy();

  /**
   * @brief Moves the provided entity using the Depth First Search strategy
   *
   * @param entity, a pointer to an IEntity object to move
   * @param dt, a double value to be moved by
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
  std::vector<std::vector<float>> path;
  int currentIndex;
  int maxIndex;
};      // end class
#endif  // DFS_STRATEGY_H_