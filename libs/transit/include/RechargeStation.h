#ifndef RECHARGE_STATION_H_
#define RECHARGE_STATION_H_

#include "IEntity.h"
#include <vector>

class RechargeStation : public IEntity{
    private:
     std::vector<BatteryDecorator*> recharging;
     JsonObject details: 
     Vector3 position;
     float speed;

    public:
     Vector3 GetPosition() const { return position; }

     Vector3 GetDirection() const { return direction; }

     Vector3 GetDestination() const { return destination; }

     JsonObject GetDetails() const { return details; }
     
     void SetPosition(Vector3 pos_) { position = pos_; }
     
     float GetSpeed() const { return speed; }
     
     void Update(double dt, std::vector<IEntity*> scheduler);  
}