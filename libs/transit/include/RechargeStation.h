#ifndef RECHARGE_STATION_H_
#define RECHARGE_STATION_H_

#include <vector>

#include "BatteryDecorator.h"
#include "IEntity.h"

/**
 * @brief Recharge Station which allows Drones to charge their batteries and
 *continue flying
 * @param obj, a memory address for a JsonObject
 **/
class RechargeStation : public IEntity {
 protected:  // since Mobile inherits these
  std::vector<BatteryDecorator*> recharging;
  JsonObject details;
  Vector3 position;
  Vector3 direction;
  Vector3 destination;
  bool available;
  float speed;

 public:
  RechargeStation(JsonObject& obj);

  ~RechargeStation() override = default;

  /**
   * @brief Returns the current position of the recharge station as a Vector3
   *object
   *
   * @return position, a Vector3
   **/
  Vector3 GetPosition() const { return position; }

  /**
   * @brief Returns the current direction of the recharge station as a Vector3
   *object
   *
   * @return direction, a Vector3
   **/
  Vector3 GetDirection() const { return direction; }

  /**
   * @brief Returns the current destination of the recharge station as a Vector3
   *object
   *
   * @return destination, a Vector3
   **/
  Vector3 GetDestination() const { return destination; }

  /**
   * @brief Returns the current availability of the recharge station as a
   *boolean value
   *
   * @return available, a true or false boolean value
   **/
  bool GetAvailability() const { return available; }

  /**
   * @brief Returns the details of the recharge station
   *
   * @return details as a JsonObject
   **/
  JsonObject GetDetails() const override;

  /**
   * @brief Sets the current availability
   *
   * @param choice, a boolean value
   * @return None
   **/
  void SetAvailability(bool choice);

  /**
   * @brief Recharges the drone
   *
   * @return None
   **/
  void recharge();

  /**
   * @brief Gets the current speed and returns it
   *
   * @return speed, the current speed
   **/
  float GetSpeed() const { return speed; }

  /**
   * @brief Updates the recharge station
   *
   * @param dt, a double delta value
   * @param scheduler, a vector array of IEntity ptrs
   *
   * @return None
   **/
  virtual void Update(double dt, std::vector<IEntity*> scheduler);

  void AddBattery(IEntity* battery);
};

#endif
