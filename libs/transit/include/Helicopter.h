#ifndef HELICOPTER_H_
#define HELICOPTER_H_

#include <stdlib.h>

#include <ctime>
#include <iostream>
#include <random>

#include "BeelineStrategy.h"
#include "IEntity.h"
#include "IStrategy.h"

/**
 * @brief the Helicopter entity class. It Creates a Helicopter entity
 * @param obj JsonObject&
 **/
class Helicopter : public IEntity {
 private:
  JsonObject details;
  Vector3 position;
  Vector3 direction;
  Vector3 destination;

  std::string strategyName;
  float speed;
  bool available;
  IStrategy* strategy = NULL;

 public:
  Helicopter(JsonObject& obj);
  ~Helicopter();

  /**
   * @brief Gets the current position of the Helicopter
   *
   * @return position, a Vector3 value
   **/
  Vector3 GetPosition() const { return position; }

  /**
   * @brief Gets the current direction of the Helicopter
   *
   * @return direction, a Vector3 value
   **/
  Vector3 GetDirection() const { return direction; }

  /**
   * @brief Gets the current Destination of the Helicopter
   *
   * @return direction, a Vector3 value
   **/
  Vector3 GetDestination() const { return destination; }

  /**
   * @brief Gets the details about the Helicopter object
   *
   * @return details, a JsonObject filled with details about the Car
   **/
  JsonObject GetDetails() const { return details; }

  /**
   * @brief Gets the current speed of the Helicopter
   *
   * @return speed, a float value
   **/
  float GetSpeed() const { return speed; }

  /**
   * @brief Update the helicopters position on using Beeline strategy
   *
   * @param dt, a double value
   * @param scheduler, a vector of type IEntity
   * @return None
   **/
  void Update(double dt, std::vector<IEntity*> scheduler);

  /**
   * @brief Sets the current position of the Helicopter
   *
   * @param pos_, a Vector3
   * @return None
   **/
  void SetPosition(Vector3 pos_) { position = pos_; }

  /**
   * @brief Sets the current direction of the Helicopter
   *
   * @param dir_, a Vector3
   * @return None
   **/
  void SetDirection(Vector3 dir_) { direction = dir_; }

  /**
   * @brief Sets the current destination of the Helicopter
   *
   * @param des_, a Vector3
   * @return None
   **/
  void SetDestination(Vector3 des_) { destination = des_; }

  Helicopter(const Helicopter& helicopter) = delete;
  Helicopter& operator=(const Helicopter& helicopter) = delete;

  /**
   * @brief Rotate the helicopter towards its destination
   *
   * @param angle, a double value
   * @return None
   **/
  void Rotate(double angle);
};
#endif
