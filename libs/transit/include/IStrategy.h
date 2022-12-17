#ifndef ISTRATEGY_H_
#define ISTRATEGY_H_

#include <vector>

#include "IEntity.h"
#include "graph.h"

using namespace routing;

/**
 * @brief Strategy class to host AStar, DFS, Dijkstra, and Beeline
 **/
class IStrategy {
 public:
  /**
   * @brief Moves the provided entity
   *
   * @param entity, a pointer to an IEntity object to be moved
   * @param dt, a double value to be moved by
   * @return None
   **/
  virtual void Move(IEntity* entity, double dt) = 0;

  /**
   * @brief Checks to see if the route is completed
   *
   * @return IsCompleted, a true or false boolean value
   **/
  virtual bool IsCompleted() = 0;

 protected:
  // IGraph object to be used in the simulation.
  const IGraph* graph;
};  // close class

#endif  // ISTRATEGY_H_