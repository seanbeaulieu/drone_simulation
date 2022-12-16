#ifndef EMERGENCY_PICKUP_H_
#define EMERGENCY_PICKUP_H_

#include <vector>

#include "IEntity.h"
#include "BatteryDecorator.h"


class EmergencyPickup : public IEntity {
 public:
  // start of .cc implemented
  EmergencyPickup(JsonObject& obj); // should we use JsonObject& obj?
  ~EmergencyPickup();
  void Update(double dt, std::vector<IEntity*> scheduler);
  //void SetStrategy(IStrategy* strategy);
  // virtual void Rotate(double angle); // implement in .cc if used
  // virtual void Jump(double height) {} // implement in .cc if used
  
  // start of .h implemented
  Vector3 GetPosition() const{ return position; }
  Vector3 GetDirection() const { return direction; }
  Vector3 GetDestination() const { return destination; }
  JsonObject GetDetails() const { return details; }
  float GetSpeed() const { return speed; }
  bool GetAvailability() { return available; }
  std::string GetStrategyName() { return strategyName; }
  void SetAvailability(bool choice) { this->available = choice; }
  void SetPosition(Vector3 pos_) { this->position = pos_; }
  void SetDirection(Vector3 dir_) { this->direction = dir_; }
  void SetDestination(Vector3 des_) { this->destination = des_; }
  void SetStrategyName(std::string strategyName_) { this->strategyName = strategyName; }
  void SetEntities(std::vector<IEntity*>* entities) { this->entities = entities; }
  void SearchDrone();

 private:
  IEntity* droneBattery = NULL;
  JsonObject details;
  Vector3 position;
  Vector3 destination;
  Vector3 direction;
  float speed;
  bool pickup = false;
  std::string strategyName;
  IStrategy* toTargetPosStrategy = NULL;
  IStrategy* toTargetDestStrategy = NULL;
  bool available = true;
  std::vector<IEntity*>* entities = NULL;
  
};

#endif
