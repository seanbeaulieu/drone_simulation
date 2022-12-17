#include "SimulationModel.h"
#include "CarFactory.h"
#include "DroneFactory.h"
#include "EM_Pickup_Factory.h"
#include "HelicopterFactory.h"
#include "LostDuckFactory.h"
#include "MobileRechargeFactory.h"
#include "RechargeStationFactory.h"
#include "RobotFactory.h"

SimulationModel::SimulationModel(IController& controller)
    : controller(controller) {
  compFactory = new CompositeFactory();
  AddFactory(new DroneFactory());
  AddFactory(new RobotFactory());
  AddFactory(new HelicopterFactory());
  AddFactory(new CarFactory());
  AddFactory(new LostDuckFactory());
  AddFactory(new RechargeStationFactory());
  AddFactory(new MobileRechargeFactory());
  AddFactory(new EM_Pickup_Factory());
}

void SimulationModel::CreateEntity(JsonObject& entity) {
  std::string type = entity["type"];
  std::string name = entity["name"];
  JsonArray position = entity["position"];
  std::cout << name << ": " << position << std::endl;

  IEntity* myNewEntity = compFactory->CreateEntity(entity);
  myNewEntity->SetGraph(graph);

  // Call AddEntity to add it to the view
  controller.AddEntity(*myNewEntity);
  entities.push_back(myNewEntity);

  // needed to search for stations or dead drones, respectively
  if (type.compare("drone") == 0 || type.compare("emergencypickup") == 0) {
    myNewEntity->SetEntities(&entities);
  }
}

/// Schedules a trip for an object in the scene
void SimulationModel::ScheduleTrip(JsonObject& details) {
  std::string name = details["name"];
  JsonArray start = details["start"];
  JsonArray end = details["end"];
  std::cout << name << ": " << start << " --> " << end << std::endl;

  for (auto entity : entities) {  // Add the entity to the scheduler
    JsonObject detailsTemp = entity->GetDetails();
    std::string nameTemp = detailsTemp["name"];
    std::string typeTemp = detailsTemp["type"];
    if (name.compare(nameTemp) == 0 && typeTemp.compare("robot") == 0 &&
        entity->GetAvailability()) {
      std::string strategyName = details["search"];
      entity->SetStrategyName(strategyName);
      entity->SetDestination(Vector3(end[0], end[1], end[2]));
      scheduler.push_back(entity);
      break;
    }
  }
  controller.SendEventToView("TripScheduled", details);
}

/// Updates the simulation
void SimulationModel::Update(double dt) {
  for (int i = 0; i < entities.size(); i++) {
    entities[i]->Update(dt, scheduler);
    controller.UpdateEntity(*entities[i]);
  }
}

void SimulationModel::AddFactory(IEntityFactory* factory) {
  compFactory->AddFactory(factory);
}
