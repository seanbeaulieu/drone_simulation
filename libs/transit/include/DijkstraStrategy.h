#ifndef Dijkstra_STRATEGY_H_
#define Dijkstra_STRATEGY_H_

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
class DijkstraStrategy : public IStrategy {
 public:
  DijkstraStrategy(Vector3 position, Vector3 destination, const IGraph* graph);
  ~DijkstraStrategy();

  /**
   * @brief Moves the provided entity using the Dijkstra strategy
   *
   * @param entity, a pointer to an IEntity object to be moved
   * @param dt, a double value to be moved by
   * @return None
   **/
  void Move(IEntity* entity, double dt);

  /**
   * @brief Checks to see if the route has been completed
   *
   * @return IsCompleted, a true or false boolean value
   **/
  bool IsCompleted();

 private:
  std::vector<std::vector<float>> path;
  int currentIndex;
  int maxIndex;
};      // end class
#endif  // Dijkstra_STRATEGY_H_