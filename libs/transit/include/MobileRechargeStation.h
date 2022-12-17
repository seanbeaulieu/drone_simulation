#ifndef MOBI_RECHARGE_ST_H_
#define MOBI_RECHARGE_ST_H_

#include <cmath>
#include <iostream>
#include <string>

#include "BeelineStrategy.h"
#include "IStrategy.h"
#include "RechargeStation.h"

/**
 * @brief Class for a Mobile Recharge Station which traverses the map
 * and allows Drones to charge their batteries
 * @param obj, a memory address for a JsonObject
 **/
class MobileRechargeStation : public RechargeStation {
 private:
  std::string strategyName;
  IStrategy* strategy = NULL;

 public:
  MobileRechargeStation(JsonObject& obj);
  ~MobileRechargeStation();

  /**
   * @brief Updates the position of the MobileRechargeStation
   *
   * @param dt, a double delta value
   * @param scheduler, a vector array of IEntity ptrs
   * @return None
   **/
  void Update(double dt, std::vector<IEntity*> scheduler);

  /**
   * @brief Sets the position of the Mobile Recharge Station
   *
   * @param pos_, a Vector3 representing the intended position
   * @return None
   **/
  void SetPosition(Vector3 pos_) { position = pos_; }

  /**
   * @brief Sets the direction of the Mobile Recharge Station
   *
   * @param dir_, a Vector3 representing the intended direction
   * @return
   **/
  void SetDirection(Vector3 dir_) { direction = dir_; }

  /**
   * @brief Sets the destination of the Mobile Recharge Station
   *
   * @param des_, a Vector3 representing the intended destination
   * @return None
   **/
  void SetDestination(Vector3 des_) { destination = des_; }

  /**
   * @brief Sets the Strategy Name of the Mobile Recharge Station
   *
   * @param strategyName, a String value of a Strategy Name
   * @return None
   **/
  void SetStrategyName(std::string strategyName);

  /**
   * @brief Sets the Strategy of the Mobile Recharge Station
   *
   * @param strategy, a IStrategy pointer representing a strategy
   * @return None
   **/
  void SetStrategy(IStrategy* strategy);

  /**
   * @brief Rotates the Mobile Recharge Station
   *
   * @param angle, a double value representing the angle to rotate
   * @return None
   **/
  void Rotate(double angle);
};

#endif
