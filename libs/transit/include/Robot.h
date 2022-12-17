#ifndef ROBOT_H
#define ROBOT_H

#include <vector>

#include "IEntity.h"
#include "math/vector3.h"
#include "util/json.h"

/**
 * @brief Robot class to represent a user to be picked up and transported
 * @param obj, a memory address for a JsonObject
 **/
class Robot : public IEntity {
 public:
  Robot(JsonObject& obj);

  ~Robot() override = default;

  /**
   * @brief Gets the current position of the Robot
   *
   * @return position, a Vector3 representing the current position of the robot
   **/
  Vector3 GetPosition() const { return position; }

  /**
   * @brief Gets the current direction of the Robot
   *
   * @return direction, a Vector3 representing the current direction of the
   *robot
   **/
  Vector3 GetDirection() const { return direction; }

  /**
   * @brief Gets the current destination of the Robot
   *
   * @return destination, a Vector3 representing the current destination of the
   *robot
   **/
  Vector3 GetDestination() const { return destination; }

  /**
   * @brief Gets the current availabilty of the Robot
   *
   * @return available, a true or false boolean value
   **/
  bool GetAvailability() const { return available; }

  /**
   * @brief Gets the details of the Robot as a JsonObject
   *
   * @return a JsonObject with the details filled in
   **/
  JsonObject GetDetails() const override;

  /**
   * @brief Gets the current speed of the robot
   *
   * @return speed, a float value representing the current speed
   **/
  float GetSpeed() const { return speed; }

  /**
   * @brief Gets the current strategy name of the Robot as a string
   *
   * @return strategyName, a string representing the strategy being used
   **/
  std::string GetStrategyName() { return strategyName; }

  /**
   * @brief Sets the availabilty of the Robot
   *
   * @param choice, a boolean value representing the intended availability
   * @return None
   **/
  void SetAvailability(bool choice);

  /**
   * @brief Sets the position of the Robot
   *
   * @param pos_, a Vector3 representing the intended position of the Robot
   * @return None
   **/
  void SetPosition(Vector3 pos_) { position = pos_; }

  /**
   * @brief Sets the direction of the Robot
   *
   * @param dir_, a Vector3 representing the intended direction of the Robot
   * @return None
   **/
  void SetDirection(Vector3 dir_) { direction = dir_; }

  /**
   * @brief Sets the destination of the Robot
   *
   * @param des_, a Vector3 representing the intended destination of the Robot
   * @return None
   **/
  void SetDestination(Vector3 des_) { destination = des_; }

  /**
   * @brief Sets the strategy name of the Robot
   *
   * @param strategyName_, a string representing the intended strategy name for
   *the Robot to use
   * @return None
   **/
  void SetStrategyName(std::string strategyName_) {
    strategyName = strategyName_;
  }

  /**
   * @brief Rotates the Robot
   *
   * @param angle, a double value to rotate by
   * @return None
   **/
  void Rotate(double angle);

 private:
  JsonObject details;
  Vector3 position;
  Vector3 direction;
  Vector3 destination;
  float speed;
  bool available;
  std::string strategyName;
};

#endif  // ROBOT_H
