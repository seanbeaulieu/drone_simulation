#ifndef DRONE_H_
#define DRONE_H_

#include <vector>

#include "IEntity.h"
#include "IStrategy.h"
#include "math/vector3.h"

/**
 * @brief Represents a drone in a physical system.
 * Drones move using euler integration based on a specified
 * velocity and direction.
 **/
class Drone : public IEntity {
 public:
  // Drones are created with a name
  Drone(JsonObject& obj);
  // Destructor
  ~Drone();

  /**
   * @brief Returns the current speed of the drone
   *
   * @return speed, a float value representing the current speed
   **/
  float GetSpeed() const { return speed; }

  /**
   * @brief Returns the current position of the drone as a Vector3 object
   *
   * @return position, Vector 3 object
   **/
  Vector3 GetPosition() const { return position; }

  /**
   * @brief Returns the current direction of the drone as a Vector3 object
   *
   * @return direction, Vector 3 object
   **/
  Vector3 GetDirection() const { return direction; }

  /**
   * @brief Returns the current destination of the drone as a Vector3 Object
   *
   * @return destination, a Vector3 object
   **/
  Vector3 GetDestination() const { return destination; }

  /**
   * @brief Returns the details of the drone
   *
   * @return details, a JsonObject
   **/
  JsonObject GetDetails() const { return details; }

  /**
   * @brief Returns the current availability of the drone
   *
   * @return available, a boolean value true or false
   **/
  bool GetAvailability() const { return available; }

  /**
   * @brief Sets the nearest entity to the drone
   *
   * @param scheduler, a vector array of IEntity ptrs
   * @return None
   **/
  void GetNearestEntity(std::vector<IEntity*> scheduler);

  /**
   * @brief Updates the drones position
   *
   * @param dt, a double delta value
   * @param scheduler, a vector array of IEntity ptrs
   * @return None
   **/
  void Update(double dt, std::vector<IEntity*> scheduler);

  /**
   * @brief Sets the current position of the drone
   *
   * @param pos, a Vector3
   * @return None
   **/
  void SetPosition(Vector3 pos_) { position = pos_; }

  /**
   * @brief Sets the current direction of the drone
   *
   * @param dir, a Vector3
   * @return None
   **/
  void SetDirection(Vector3 dir_) { direction = dir_; }

  /**
   * @brief Sets the current destination of the drone
   *
   * @param des, a Vector3
   * @return None
   **/
  void SetDestination(Vector3 des_) { destination = des_; }

  /**
   * @brief Sets the current availability of the drone
   *
   * @param choice, a bool
   * @return None
   **/
  void SetAvailability(bool choice) { available = choice; }

  /**
   * @brief Returns the nearest entity to the drone
   *
   * @return nearestEntity, the closest entity to the drone
   **/
  IEntity* ReturnNearestEntity() { return nearestEntity; }

  /**
   * @brief Rotates the drone
   *
   * @param angle, a double value amount to rotate
   * @return None
   **/
  void Rotate(double angle);

  /**
   * @brief Jumps the drone
   *
   * @param height, the double value amount to elevate into the air
   * @return None
   **/
  void Jump(double height);

  // Removing the copy constructor and assignment operator
  // so that drones cannot be coppied.
  Drone(const Drone& drone) = delete;
  Drone& operator=(const Drone& drone) = delete;

 private:
  JsonObject details;
  Vector3 position;
  Vector3 direction;
  float jumpHeight = 0;
  bool goUp = true;  // jump helper
  Vector3 destination;
  float speed;
  bool available;
  bool pickedUp;
  std::string strategyName;
  IEntity* nearestEntity = NULL;
  IStrategy* toTargetPosStrategy = NULL;
  IStrategy* toTargetDestStrategy = NULL;
};

#endif
