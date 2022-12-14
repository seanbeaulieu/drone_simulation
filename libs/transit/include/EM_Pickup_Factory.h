#ifndef Emergency_P_F_H_
#define Emergency_P_F_H_

#include "IEntity.h"
#include "IEntityFactory.h"
#include "EmergencyPickup.h"
#include "BatteryDecorator.h"

class EM_Pickup_Factory : public IEntityFactory {
  public:
    virtual ~EM_Pickup_Factory() {}
    IEntity* CreateEntity(JsonObject& entity);
};

#endif