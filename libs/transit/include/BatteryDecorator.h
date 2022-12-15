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
    
public:
    BatteryDecorator(Drone* drone);
    BatteryDecorator(JsonObject& obj);
    ~BatteryDecorator();
    void GetNearestEntity(std::vector<IEntity*> scheduler);
    void Update(double dt, std::vector<IEntity*> scheduler);
    void Recharge(double amount);
    
    // getters
    Drone* GetDrone() const { return drone; }
    double GetCharge() const { return charge; }
    int GetId() const { return drone->GetId(); }
    float GetSpeed() const { return drone->GetSpeed(); }
	Vector3 GetPosition() const { return drone->GetPosition(); }
	Vector3 GetDirection() const { return drone->GetDirection(); }
	Vector3 GetDestination() const { return drone->GetDestination(); }
	JsonObject GetDetails() const { return drone->GetDetails(); }
	bool GetAvailability() const { return drone->GetAvailability(); }
	bool GetCharging() const { return charging; }
	std::string GetStrategyName(){ return drone->GetStrategyName(); }
	
	// setters
	void SetGraph(const IGraph* graph) { this->graph = graph; drone->SetGraph(graph); }
	void SetPosition(Vector3 pos_) { drone->SetPosition(pos_); }
	void SetDirection(Vector3 dir_) { drone->SetDirection(dir_); }
	void SetDestination(Vector3 des_) { drone->SetDestination(des_); }
	void SetAvailability(bool choice) { drone->SetAvailability(choice); }
	void SetStrategyName(std::string strategyName_) { drone->SetStrategyName(strategyName_); }
	void Rotate(double angle) { drone->Rotate(angle); }
	void Jump(double height) { drone->Jump(height); }
	
	// removing assignment operator and copy constructor to mirror drones
	BatteryDecorator(const BatteryDecorator& btry) = delete;
	BatteryDecorator& operator=(const BatteryDecorator& btry) = delete;
};

#endif
