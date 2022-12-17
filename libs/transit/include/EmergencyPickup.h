#ifndef EMERGENCY_PICKUP_H_
#define EMERGENCY_PICKUP_H_

#include <vector>

#include "BatteryDecorator.h"
#include "IEntity.h"

/**
 * @brief A new entity called EmergencyPick is responsible for picking up the
 *drone if it runs out of battery.
 **/
class EmergencyPickup : public IEntity {
 public:
  // start of .cc implemented
  EmergencyPickup(JsonObject& obj);  // should we use JsonObject& obj?
  ~EmergencyPickup();

  /**
   * @brief Updates the emergency pickup drone
   *
   * @param dt, a double delta value
   * @param scheduler, a vector array of IEntity ptrs
   * @return None
   **/
  void Update(double dt, std::vector<IEntity*> scheduler);

  /**
   * @brief Returns the current position of the emergency pickup drone as a
   *Vector3 object
   *
   * @return position, a Vector3 object
   **/
  Vector3 GetPosition() const { return position; }

  /**
   * @brief Returns the current direction of the emergency pickup drone as a
   *Vector3 object
   *
   * @return direction, a Vector3 object
   **/
  Vector3 GetDirection() const { return direction; }

  /**
   * @brief Returns the current destination of the emergency pickup drone as a
   *Vector3 Object
   *
   * @return destination, a Vector3 object
   **/
  Vector3 GetDestination() const { return destination; }

  /**
   * @brief Returns the details of the emergency pickup drone
   *
   * @return details, a JsonObject
   **/
  JsonObject GetDetails() const { return details; }

  /**
   * @brief Returns the current speed of the emergency pickup drone
   *
   * @return speed, a float value representing the current speed
   **/
  float GetSpeed() const { return speed; }

  /**
   * @brief Returns the current availability of the emergency pickup drone
   *
   * @return available, a boolean value true or false
   **/
  bool GetAvailability() { return available; }

  /**
   * @brief Returns the current strategy name of the emergency pickup drone
   *
   * @return strategyName, a String representing the strategies name
   **/
  std::string GetStrategyName() { return strategyName; }

  /**
   * @brief Sets the current availability of the emergency pickup drone
   *
   * @param choice, a boolean value
   * @return None
   **/
  void SetAvailability(bool choice) { this->available = choice; }

  /**
   * @brief Sets the current position of the emergency pickup drone
   *
   * @param pos, a Vector3 value
   * @return None
   **/
  void SetPosition(Vector3 pos_) { this->position = pos_; }

  /**
   * @brief Sets the current direction of the emergency pickup drone
   *
   * @param dir, a Vector3 value
   * @return None
   **/
  void SetDirection(Vector3 dir_) { this->direction = dir_; }

  /**
   * @brief Sets the current destination of the emergency pickup drone
   *
   * @param des, a Vector3 value
   * @return None
   **/
  void SetDestination(Vector3 des_) { this->destination = des_; }

  /**
   * @brief Sets the strategy name of the emergency pickup drone
   *
   * @param strategyName, the string name of the strategy
   * @return None
   **/
  void SetStrategyName(std::string strategyName_) {
    this->strategyName = strategyName;
  }

  /**
   * @brief Sets the entities in the vector array entities
   *
   * @param entities, a vector3 array of IEntity ptrs
   * @return None
   **/
  void SetEntities(std::vector<IEntity*>* entities) {
    this->entities = entities;
  }

  /**
   * @brief Searches for the first drone in the entities
   *
   * @return None
   **/
  void SearchDrone();

  /**
   * @brief Rotates the emergency pickup drone
   *
   * @param angle, a double amount to rotate
   * @return None
   **/
  void Rotate(double angle);

 private:
  IEntity* droneBattery = NULL;
  JsonObject details;
  Vector3 position;
  Vector3 destination;
  Vector3 direction;
  float speed;
  std::string strategyName;
  IStrategy* toTargetPosStrategy = NULL;
  IStrategy* toTargetDestStrategy = NULL;
  bool available = true;
  std::vector<IEntity*>* entities = NULL;
};

#endif
