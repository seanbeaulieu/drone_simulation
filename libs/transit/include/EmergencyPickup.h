#ifndef EMERGENCY_PICKUP_H_
#define EMERGENCY_PICKUP_H_

#include <vector>

#include "IEntity.h"
#include "BatteryDecorator.h"


class EmergencyPickup : public IEntity {
 public:
  // start of .cc implemented
  EmergencyPickup(); // should we use JsonObject& obj?
  ~EmergencyPickup();
  virtual void Update(double dt, std::vector<IEntity*> scheduler);
  void SetStrategy(IStrategy* strategy);
  // virtual void Rotate(double angle); // implement in .cc if used
  // virtual void Jump(double height) {} // implement in .cc if used
  
  // start of .h implemented
  Vector3 GetPosition() { return position; }
  Vector3 GetDirection() { return direction; }
  Vector3 GetDestination() { return destination; }
  JsonObject GetDetails() { return details; }
  float GetSpeed() { return speed; }
  bool GetAvailability() { return available; }
  std::string GetStrategyName() { return strategyName; }
  virtual void SetAvailability(bool choice) { this->available = choice; }
  virtual void SetPosition(Vector3 pos_) { this->position = pos_; }
  virtual void SetDirection(Vector3 dir_) { this->direction = dir_; }
  virtual void SetDestination(Vector3 des_) { this->destination = des_; }
  virtual void SetStrategyName(std::string strategyName_) { this->strategyName = strategyName; }

 private:
  BatteryDecorator* droneBattery;
  JsonObject details;
  Vector3 position;
  Vector3 destination;
  Vector3 direction;
  float speed;
  std::string strategyName;
  IStrategy* strategy;
  bool available;
  
};

#endif
