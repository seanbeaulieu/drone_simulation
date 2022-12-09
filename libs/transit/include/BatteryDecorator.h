#ifndef BATTERY_DECORATOR_H_
#define BATTERY_DECORATOR_H_

#include "Drone.h"
#include "IEntity.h"//fixme: drone of IEntity
class BatteryDecorator : public Drone
{
private:
    double charge;
    Drone* drone;
public:
    BatteryDecorator(JsonObject& entity);
    ~BatteryDecorator();
    //void SetDrone(Drone* drone);
    void GetNearestEntity(std::vector<IEntity*> scheduler);
    void Update(double dt, std::vector<IEntity*> scheduler);
};

#endif