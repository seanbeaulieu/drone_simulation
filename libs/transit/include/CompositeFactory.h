#ifndef COMPOSITE_FACTORY_H_
#define COMPOSITE_FACTORY_H_

#include "IEntityFactory.h"

/**
 * @brief A compositefactory for all other Factory
 **/
class CompositeFactory : public IEntityFactory {
 public:
  /**
   * @brief Creates a new entity
   *
   * @param entity, a memory address to a JsonObject
   * @return None
   **/
  IEntity* CreateEntity(JsonObject& entity);

  /**
   * @brief Adds a new type of factory to the simulation
   *
   * @param factoryEnitity, a pointer to an IEntityFactory type object
   * @return None
   **/
  void AddFactory(IEntityFactory* factoryEntity);

  virtual ~CompositeFactory();

 private:
  std::vector<IEntityFactory*> componentFactories;
};

#endif