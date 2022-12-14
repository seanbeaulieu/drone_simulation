#ifndef RECHARGE_STATION_H_
#define RECHARGE_STATION_H_

#include "IEntity.h"
#include <vector>
class RechargeStation : public IEntity{
    protected:
     //std::vector<BatteryDecorator*> recharging;
     JsonObject details;
     Vector3 position;
     Vector3 direction;
     Vector3 destination;
     bool available;
     float speed;

    public:
     RechargeStation(JsonObject &obj);

     ~RechargeStation() override = default;

     Vector3 GetPosition() const { return position; }

     Vector3 GetDirection() const { return direction; }
     
     Vector3 GetDestination() const { return destination; }

     bool GetAvailability() const { return available; }
     
     JsonObject GetDetails() const override;

     void SetAvailability(bool choice);

     void recharge();

     float GetSpeed() const { return speed; }
     
     virtual void Update(double dt, std::vector<IEntity*> scheduler) {};  
};

#endif