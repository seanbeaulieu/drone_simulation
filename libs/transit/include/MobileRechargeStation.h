#ifndef MOBI_RECHARGE_ST_H_
#define MOBI_RECHARGE_ST_H_

#include "RechargeStation.h"
#include "IStrategy.h"
#include "BeelineStrategy.h"
#include <iostream>
#include <string>
#include <cmath>
class MobileRechargeStation : public RechargeStation{
    private:
     std::string strategyName;
     IStrategy* strategy = NULL;
    //  float radius = 1000;
    //  float center_x = 0;
    //  float center_y = 0;
    //  float period = 5.0;
    //  float pi = M_PI;
    public:
     MobileRechargeStation(JsonObject &obj);
     ~MobileRechargeStation();
     void Update(double dt, std::vector<IEntity*> scheduler);
     void SetPosition(Vector3 pos_) { position = pos_; }
     void SetDirection(Vector3 dir_) { direction = dir_; }
     void SetDestination(Vector3 des_) { destination = des_; }
     void SetStrategyName(std::string strategyName);
     void SetStrategy(IStrategy* strategy);
     void Rotate(double angle);

};

#endif
