#ifndef BATTERY_DECORATOR_H_
#define BATTERY_DECORATOR_H_

#include "Drone.h"
#include "IEntity.h"//fixme: drone of IEntity
#include "BeelineStrategy.h"
class BatteryDecorator : public IEntity
{
private:
    double charge = 100;
    Drone* drone = NULL;
    bool charging = false;
    Vector3 position;
    Vector3 rechargeDest;
    IEntity* nearestRecharge = NULL;
    bool nearIsMobile = true;
    IStrategy* rechargeStrategy = NULL;
    std::vector<IEntity*>* entities = NULL; // POINTER to find nearest recharge
    bool emergency = false;
    
public:
    BatteryDecorator(Drone* drone);
    BatteryDecorator(JsonObject& obj);
    ~BatteryDecorator();
    /**
    * @brief Returns the nearest recharge station
    * 
    * @param search, a vector array of IEntity ptrs
    * @return nearestRecharge, the closest recharge station to the drone
    **/
    IEntity* GetNearestRecharge(std::vector<IEntity*> search); // find recharge station

    /**
    * @brief Calculates the trip distance for a passenger ride
    * 
    * @param passenger, a pointer to an IEntity object
    * @return a double trip distance value
    **/
    double TripDistance(IEntity* passenger); // calculate trip distance

    /**
    * @brief Finds the neartest entity 
    * 
    * @param scheduler, a vector array of IEntity ptrs
    * @return None
    **/
    void GetNearestEntity(std::vector<IEntity*> scheduler); // mimic drone

    /**
     * @brief Updates the drones position
     * 
     * @param dt, a double delta value 
     * @param scheduler, a vector array of IEntity ptrs
     * @return None
     **/
    void Update(double dt, std::vector<IEntity*> scheduler);

    /**
     * @brief Recharges the drones battery
     * 
     * @param amount, a double value signaling the amount to recharge by
     * @return None
     **/
    void Recharge(double amount); // called by recharge stations
    
    // getters

    /**
     * @brief Returns the current drone
     * 
     * @return drone, a Drone object pointer
     **/
    Drone* GetDrone() const { return drone; }

    /**
     * @brief Returns the current recharge destination of the Drone
     * 
     * @return rechargeDest, a Vector3
     **/
    Vector3 GetRechargeDest() const { return rechargeDest; }

    /**
     * @brief Returns the current charge in the battery of the drone
     * 
     * @return charge, a double value
     **/
    double GetCharge() const { return charge; }

    /**
     * @brief Returns the ID of the drone
     * 
     * @return an int value representing the drones ID
     **/
    int GetId() const { return drone->GetId(); }

    /**
     * @brief Returns the current speed of the drone
     * 
     * @return speed, a float value representing the current speed
     **/
    float GetSpeed() const { return drone->GetSpeed(); }

    /**
     * @brief Returns the current position of the drone
     * 
     * @return pos, a Vector3 representing the current position
     **/
	Vector3 GetPosition() const { return drone->GetPosition(); }

    /**
     * @brief Returns the current direction of the Drone
     * 
     * @return dir, a Vector3 representing the current direction
     **/
	Vector3 GetDirection() const { return drone->GetDirection(); }

    /**
     * @brief Returns the current destination of the drone
     * 
     * @return des, a Vector3 representing the current destination
     **/
	Vector3 GetDestination() const { return drone->GetDestination(); }

    /**
     * @brief Returns the details of the Drone
     * 
     * @return details, a JsonObject
     **/
	JsonObject GetDetails() const { return drone->GetDetails(); }

    /**
     * @brief Returns the current availability of the Drone
     * 
     * @return available, a boolean true or false value 
     **/
	bool GetAvailability() const { return drone->GetAvailability(); }

    /**
     * @brief Returns the current charging status of the drone
     * 
     * @return charging, a boolean value indicating whether the Drone is charging or not
     **/
	bool GetCharging() const { return charging; }

    /**
     * @brief Returns the current strategy name of the Drone
     * 
     * @return the string strategy name that the Drone is using
     **/
	std::string GetStrategyName(){ return drone->GetStrategyName(); }

    /**
     * @brief Returns the current emergency status of the Drone
     * 
     * @return emergency, a boolean value representing whether the Drone is in a state of emergency or not
     **/
    bool GetEmergency() const { return emergency; }
	
	// setters

    /**
     * @brief Sets the entities in the provided vector array
     * 
     * @param entities, a vector array of IEntity ptrs
     * 
     * @return None
     **/
	void SetEntities(std::vector<IEntity*>* entities) { this->entities = entities; }

    /**
     * @brief Sets the graph of the drone
     * 
     * @param graph, a pointer to an IGraph 
     * 
     * @return None
     **/
	void SetGraph(const IGraph* graph) { this->graph = graph; drone->SetGraph(graph); }

    /**
     * @brief Sets the position of the Drone
     * 
     * @param pos_, a Vector3 representing the intended position
     * 
     * @return None
     **/
	void SetPosition(Vector3 pos_) { drone->SetPosition(pos_); }

    /**
     * @brief Sets the direction of the Drone
     * 
     * @param dir_, a Vector3 representing the intended direction
     * 
     * @return None
     **/
	void SetDirection(Vector3 dir_) { drone->SetDirection(dir_); }

    /**
     * @brief Sets the destination of the Drone
     * 
     * @param des_, a Vector3 representing the intended destination
     * 
     * @return None
     **/
	void SetDestination(Vector3 des_) { drone->SetDestination(des_); }

    /**
     * @brief Sets the availability status of the Drone
     * 
     * @param choice, a boolean true or false value
     * 
     * @return None
     **/
	void SetAvailability(bool choice) { drone->SetAvailability(choice); }

    /**
     * @brief Sets the strategy name for the Drone to use
     * 
     * @param strategyName_, the intended strategy as a String
     * 
     * @return None
     **/
	void SetStrategyName(std::string strategyName_) { drone->SetStrategyName(strategyName_); }

    /**
     * @brief Rotates the drone
     * 
     * @param angle, a double value amount to rotate
     * @return None
     **/
	void Rotate(double angle) { drone->Rotate(angle); }

    /**
     * @brief Jumps the drone
     * 
     * @param height, the double value amount to elevate into the air
     * @return None
     **/
	void Jump(double height) { drone->Jump(height); }
	
	// removing assignment operator and copy constructor to mirror drones
	BatteryDecorator(const BatteryDecorator& btry) = delete;
	BatteryDecorator& operator=(const BatteryDecorator& btry) = delete;
};

#endif
