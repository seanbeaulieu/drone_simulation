#ifndef CAR_H_
#define CAR_H_

#include <vector>

#include "IEntity.h"
#include "IStrategy.h"
#include "math/vector3.h"

/**
 * @brief the car entity class. It Creates a Car entity
 * @param obj, an JsonObject&
 **/
class Car : public IEntity {
 public:
  Car(JsonObject& obj);
  ~Car();
  void Update(double dt, std::vector<IEntity*> scheduler);

  /**
   * @brief Sets the current position of the Car
   *
   * @param pos_, a Vector3
   * @return None
   **/
  void SetPosition(Vector3 pos_);

  /**
   * @brief Sets the current direction of the Car
   *
   * @param dir_, a Vector3
   * @return None
   **/
  void SetDirection(Vector3 dir_);

  /**
   * @brief Set the destionation of the Car
   *
   * @param des_, a Vector3
   * @return None
   **/
  void SetDestination(Vector3 des_);

  /**
   * @brief Gets the current position of the Car
   *
   * @return position, a Vector3 value
   **/
  Vector3 GetPosition() const;

  /**
   * @brief Gets the current direction of the Car
   *
   * @return direction, a Vector3 value
   **/
  Vector3 GetDirection() const;

  /**
   * @brief Gets the current destination of the Car
   *
   * @return destination, a Vector 3 value
   **/
  Vector3 GetDestination() const;

  /**
   * @brief Gets the details about the Car object
   *
   * @return details, a JsonObject filled with details about the Car
   **/
  JsonObject GetDetails() const;

  /**
   * @brief Gets the current speed of the Car
   *
   * @return speed, a float value
   **/
  float GetSpeed() const;

 private:
  JsonObject details;
  Vector3 position;
  Vector3 direction;
  Vector3 destination;
  float speed;
  IStrategy* strategy = NULL;
};

#endif
