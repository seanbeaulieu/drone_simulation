#ifndef MOBI_RECHARGE_ST_H_
#define MOBI_RECHARGE_ST_H_

#include "RechargeStation.h"
#include "IStrategy.h"
class MobileRechargeStation : public RechargeStation{
    private:
     std::string strategyName;
     IStrategy* strategy;
     Vector3 destination;
     Vector3 direction;

    public:
     Vector3 GetPosition() const { return position; }
     Vector3 GetDirection() const { return direction; }
     Vector3 GetDestination() const { return destination; }
     float GetSpeed() const { return speed; }
     void Update(double dt, std::vector<IEntity*> scheduler);
     void SetPosition(Vector3 pos_) { position = pos_; }
     void SetDirection(Vector3 dir_) { direction = dir_; }
     void SetDestination(Vector3 des_) { destination = des_; }
     void SetStrategyName(std::string strategyName);
     void SetStrategy(IStrategy* strategy);
    

}