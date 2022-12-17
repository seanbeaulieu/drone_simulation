#ifndef CONTROLLER_H_
#define CONTROLLER_H_

#include "IEntity.h"
#include "util/json.h"

//--------------------  Controller Interface ----------------------------

/**
 * @brief Abstract controller class used in the Transit Service.  Uses the Model
 *View
 **/

/// Controller Pattern
class IController {
 public:
  virtual ~IController() {}
  /// Adds an entity to the program

  /**
   * @brief Adds an entity to the program
   *
   * @param entity, a memory address of an IEntity
   * @return None
   **/
  virtual void AddEntity(const IEntity& entity) = 0;

  /**
   * @brief Updates an entity in the program
   *
   * @param entity, a memory address of an IEntity
   * @return None
   **/
  virtual void UpdateEntity(const IEntity& entity) = 0;
  /// Removes an entity from the program

  /**
   * @brief Removes an entity from the program
   *
   * @param id, the id of the entity to remove
   * @return None
   **/
  virtual void RemoveEntity(int id) = 0;

  /// Adds a path to the program
  /**
   * @brief Adds a path to the program
   *
   * @param id, the id of an entity
   * @param path, the memory address path in the vector array of floats
   * @return None
   **/
  virtual void AddPath(int id,
                       const std::vector<std::vector<float> >& path) = 0;

  /// Removes a path from the program
  /**
   * @brief Removes a path
   *
   * @param id, the int id to remove
   * @return None
   **/
  virtual void RemovePath(int id) = 0;

  /// Allows messages to be passed back to the view
  /**
   * @brief Allows messages to be passed back to the view
   *
   * @param event, a memory address to a string message
   * @param details, a memory address to a JsonObject
   * @return None
   **/
  virtual void SendEventToView(const std::string& event,
                               const JsonObject& details) = 0;
};

#endif
