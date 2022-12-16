#ifndef MRF_H_
#define MRF_H_

#include "MobileRechargeStation.h"
#include "IEntity.h"
#include "IEntityFactory.h"

class MobileRechargeFactory : public IEntityFactory{
 public:
  virtual ~MobileRechargeFactory() {}

  /**
     * @brief Creates a new Mobile Recharge Factory entity
     * 
     * @param entity, a memory address to a JsonObject
     * @return a pointer to the newly created Mobile Recharge Factory
     **/
  IEntity* CreateEntity(JsonObject& entity);
};

#endif