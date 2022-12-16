#ifndef LOST_DUCK_H_
#define LOST_DUCK_H_

#include <stdlib.h>

#include <ctime>
#include <iostream>
#include <random>

#include "AstarStrategy.h"
#include "DijkstraStrategy.h"
#include "IEntity.h"
#include "IStrategy.h"

/**
 * @brief the Lost_Duck entity class. It Creates a Lost_Duck entity
 * @param obj JsonObject&
 **/
class Lost_Duck : public IEntity {
 private:
  JsonObject details;
  Vector3 position;
  Vector3 direction;
  Vector3 destination;

  std::string strategyName;
  float speed;
  bool available;
  IStrategy* strategy = NULL;
  IStrategy* strat2 = NULL;
  float time;

 public:
  Lost_Duck(JsonObject& obj);
  ~Lost_Duck();

  /**
   * @brief Gets the current position of the Lost_Duck
   *
   * @return position, a Vector3 value
   **/
  Vector3 GetPosition() const { return position; }

  /**
   * @brief Gets the current direction of the Lost_Duck
   *
   * @return direction, a Vector3 value
   **/
  Vector3 GetDirection() const { return direction; }

  /**
   * @brief Gets the current Destination of the Lost_Duck
   *
   * @return direction, a Vector3 value
   **/
  Vector3 GetDestination() const { return destination; }

  /**
   * @brief Gets the details about the Lost_Duck object
   *
   * @return details, a JsonObject filled with details about the Car
   **/
  JsonObject GetDetails() const { return details; }

  /**
   * @brief Gets the current speed of the Lost_Duck
   *
   * @return speed, a float value
   **/
  float GetSpeed() const { return speed; }

  /**
   * @brief Update the Lost_ducks position on using Dijk strategy
   *
   * @param dt, a double value
   * @param scheduler, a vector of type IEntity
   * @return None
   **/
  void Update(double dt, std::vector<IEntity*> scheduler);

  /**
   * @brief Sets the current position of the Lost_Duck
   *
   * @param pos_, a Vector3
   * @return None
   **/
  void SetPosition(Vector3 pos_) { position = pos_; }

  /**
   * @brief Sets the current direction of the Lost_Duck
   *
   * @param dir_, a Vector3
   * @return None
   **/
  void SetDirection(Vector3 dir_) { direction = dir_; }

  /**
   * @brief Sets the current destination of the Lost_Duck
   *
   * @param des_, a Vector3
   * @return None
   **/
  void SetDestination(Vector3 des_) { destination = des_; }

  Lost_Duck(const Lost_Duck& duck) = delete;
  Lost_Duck& operator=(const Lost_Duck& duck) = delete;

  /**
   * @brief Rotate the Lost_ducks towards its destination
   *
   * @param angle, a double value
   * @return None
   **/
  void Rotate(double angle);
};
#endif
