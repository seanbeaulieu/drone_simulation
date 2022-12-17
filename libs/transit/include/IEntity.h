#ifndef ENTITY_H_
#define ENTITY_H_

#include <vector>

#include "graph.h"
#include "math/vector3.h"
#include "util/json.h"

using namespace routing;

//--------------------  Controller Interface ----------------------------

/// Abstract controller class used in the Transit Service.  Uses the Model View
/// Controller Pattern

/**
 * @brief all object int he simulation model
 */

class IEntity {
 public:
  IEntity() {
    static int currentId = 0;
    id = currentId;
    currentId++;
  }
  virtual ~IEntity() {}

  /**
   * @brief Returns the ID of the entity
   *
   * @return an integer ID
   **/
  virtual int GetId() const { return id; }

  /**
   * @brief Returns the current position of the entity as a Vector3 object
   *
   * @return Vector 3 object
   **/
  virtual Vector3 GetPosition() const = 0;

  /**
   * @brief Returns the current direction of the entity as a Vector3 object
   *
   * @return Vector 3 object
   **/
  virtual Vector3 GetDirection() const = 0;

  /**
   * @brief Returns the current destination of the entity as a Vector3 Object
   *
   * @return Vector 3 object
   **/
  virtual Vector3 GetDestination() const = 0;

  /**
   * @brief Returns the details of the entity
   *
   * @return details as a JsonObject
   **/
  virtual JsonObject GetDetails() const = 0;

  /**
   * @brief Returns the current speed of the entity
   *
   * @return a float value representing the current speed
   **/
  virtual float GetSpeed() const = 0;

  /**
   * @brief Returns the current availability of the entity
   *
   * @return boolean value true or false
   **/
  virtual bool GetAvailability() const {};

  /**
   * @brief Returns the current strategy name of the entity
   *
   * @return String representing the strategies name
   **/
  virtual std::string GetStrategyName() {}

  /**
   * @brief Sets the current availability of the entity
   *
   * @param choice, a boolean value
   * @return None
   **/
  virtual void SetAvailability(bool choice) {}

  /**
   * @brief Updates the entity
   *
   * @param dt, a double delta value
   * @param scheduler, a vector array of IEntity ptrs
   * @return None
   **/
  virtual void Update(double dt, std::vector<IEntity*> scheduler) {}

  /**
   * @brief Sets the graph of the entity
   *
   * @param IGraph graph
   * @return None
   **/
  virtual void SetGraph(const IGraph* graph) { this->graph = graph; }

  /**
   * @brief Sets the current position of the entity
   *
   * @param pos_, a vector3 value
   * @return None
   **/
  virtual void SetPosition(Vector3 pos_) {}

  /**
   * @brief Sets the current direction of the entity
   *
   * @param dir, a vector3 value
   * @return None
   **/
  virtual void SetDirection(Vector3 dir_) {}

  /**
   * @brief Sets the current destination of the entity
   *
   * @param des, a vector3 value
   * @return None
   **/
  virtual void SetDestination(Vector3 des_) {}

  /**
   * @brief Sets the strategy of the Entity
   *
   * @param strategyName, string name of the strategy
   * @return None
   **/
  virtual void SetStrategyName(std::string strategyName_) {}

  /**
   * @brief Rotates the entity
   *
   * @param angle, a double amount to rotate
   * @return None
   **/
  virtual void Rotate(double angle) {}

  /**
   * @brief Jumps the entity
   *
   * @param height, a double amount to elevate into the air
   * @return None
   **/
  virtual void Jump(double height) {}

  /**
   * @brief Sets the entities into a vector array of IEntitys
   *
   * @param entities, a vector array of IEntity ptrs
   * @return None
   **/
  virtual void SetEntities(std::vector<IEntity*>* entities) {}
  virtual bool GetEmergency() const { return false; }
  virtual void SetEmergency(bool choice) {}
  virtual IEntity* GetNearestRecharge(std::vector<IEntity*> search) {
    return nullptr;
  }
  virtual void AddBattery(IEntity* battery) {}

 protected:
  int id;
  const IGraph* graph;
};

#endif
