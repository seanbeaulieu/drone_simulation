#ifndef SIMULATION_MODEL_H_
#define SIMULATION_MODEL_H_

#include "CompositeFactory.h"
#include "IController.h"
#include "IEntity.h"
#include "graph.h"
using namespace routing;

//--------------------  Model ----------------------------

/// Simulation Model handling the transit simulation.  The model can communicate
/// with the controller.
/**
 * @brief Simulation Model class handling the transit simulation. The model can
 *communicate with the controller.
 * @param controller, a memory address for an IController
 **/
class SimulationModel {
 public:
  SimulationModel(IController& controller);

  /**
   * @brief Sets the graph of the Simulation
   *
   * @param graph, a pointer to an IGraph object
   * @return None
   **/
  void SetGraph(const IGraph* graph) { this->graph = graph; }

  /// Creates an simulation entity
  /**
   * @brief Creates a simulation entity
   *
   * @param entity, a memory address of a JsonObject
   * @return None
   **/
  void CreateEntity(JsonObject& entity);

  /// Schedules a trip for an object in the scene
  /**
   * @brief Schedules a trip for an object in the scene
   *
   * @param details, a memory address of a JsonObject
   * @return None
   **/
  void ScheduleTrip(JsonObject& details);

  /// Updates the simulation
  /**
   * @brief Updates the simulation
   *
   * @param dt, a double value to update by
   * @return None
   **/
  void Update(double dt);

  // Adds a new entity type
  /**
   * @brief Adds a new type of entity to be made
   *
   * @param factory, a pointer to a IEntityFactory type object
   * @return None
   **/
  void AddFactory(IEntityFactory* factory);

 protected:
  IController& controller;
  std::vector<IEntity*> entities;
  std::vector<IEntity*> scheduler;
  const IGraph* graph;
  CompositeFactory* compFactory;
};

#endif
