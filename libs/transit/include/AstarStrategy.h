#ifndef ASTAR_STRATEGY_H_
#define ASTAR_STRATEGY_H_

/**
 * include
 */
#include "math/vector3.h"
#include <vector>
#include "IStrategy.h"
#include "IEntity.h"
/**
 * @brief this class inhertis from the IStrategy class and is responsible for generating the beeline that the drone will take.
 */
class AstarStrategy : public IStrategy {
public:
    AstarStrategy(Vector3 position, Vector3 destination, const IGraph* graph);
    ~AstarStrategy();

    /**
     * @brief Moves an entity using the AStar strategy
     * 
     * @param entity, a pointer to an IEntity object to be moved
     * @return None
     **/
    void Move(IEntity* entity, double dt);

    /**
     * @brief Checks to see if a route is completed
     * 
     * @return IsCompleted, a true or false boolean value
     **/
    bool IsCompleted();

private:
    std::vector<std::vector<float>> path;
    int currentIndex;
    int maxIndex;
}; //end class
#endif // ASTAR_STRATEGY_H_