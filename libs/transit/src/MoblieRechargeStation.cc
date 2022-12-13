#include "MobileRechargeStation.h"


MobileRechargeStation :: MobileRechargeStation(JsonObject &obj) : RechargeStation(obj){
   
}

void MobileRechargeStation :: SetStrategyName(std::string strategyName){
    //fixme later need startey name???
    return;
}

void MobileRechargeStation :: SetStrategy(IStrategy* strategy){
    //fixme later
    return;
}

void MobileRechargeStation:: Update(double dt, std::vector<IEntity*> scheduler){

}