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

     JsonObject GetDetails() const { return details; }
     
     void SetPosition(Vector3 pos_) { position = pos_; }
     

     virtual void Update(double dt, std::vector<IEntity*> scheduler);  
}