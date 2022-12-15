#include "MoblieRechargeFactory.h"

IEntity* MoblieRechargeFactory::CreateEntity(JsonObject& entity){
    std::string type = entity["type"];
    if(type.compare("moblierecharge") == 0){
        std::cout<<"MoblieRecharge Created" << std::endl;
        return new MobileRechargeStation(entity);
    }
    return nullptr;
}
