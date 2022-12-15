#ifndef MRF_H_
#define MRF_H_

#include "MobileRechargeStation.h"
#include "IEntity.h"
#include "IEntityFactory.h"

class MoblieRechargeFactory : public IEntityFactory{
 public:
  virtual ~MoblieRechargeFactory() {}
  IEntity* CreateEntity(JsonObject& entity);
};

#endif
