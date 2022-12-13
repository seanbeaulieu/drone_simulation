#ifndef RST_H_
#define RST_H_

#include "RechargeStation.h"
#include "IEntity.h"
#include "IEntityFactory.h"
    
class RechargeStationFactory : public IEntityFactory{
 public:
  virtual ~RechargeStationFactory() {}
  IEntity* CreateEntity(JsonObject& entity);
};

#endif