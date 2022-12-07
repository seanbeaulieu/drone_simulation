#ifndef BATTERY_DECORATOR_H_
#define BATTERY_DECORATOR_H_

#include "Drone.h"

class BatteryDecorator : public Drone
{
private:
    double charge;
    Drone* drone;
public:
    BatteryDecorator();
    ~BatteryDecorator();
    void Update(double dt, std::vector<IEntity*> scheduler)
};


