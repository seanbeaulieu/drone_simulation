#include "BatteryDecorator.h"

BatteryDecorator :: BatteryDecorator(Drone* drone) {
	this->drone = drone;
}

BatteryDecorator :: BatteryDecorator(JsonObject& obj) {
	drone = new Drone(obj);
}

BatteryDecorator :: ~BatteryDecorator(){
    if (drone) {
		delete drone;
	}
}

void BatteryDecorator::GetNearestEntity(std::vector<IEntity*> scheduler){
    drone->GetNearestEntity(scheduler);
}

void BatteryDecorator::Update(double dt, std::vector<IEntity*> scheduler){
// TODO: Implement logic
/*
    position = this->GetPosition();
    if (charge > 0){
       drone->Update(dt, scheduler); 
    }
    if(this->GetPosition().Distance(position) > 0.001){
       charge -= dt;
       std::cout<<"charge is: "<<charge<<std::endl; 
    }
<<<<<<< HEAD
*/

	// note: may need a way to broadcast a dead battery to emergency pickup?
	
	// current implementation allows battery failure due to the mobile recharge station,
	// which is both less difficult on us and can actually showcase the pickup
	
	if (charge <= 0) {
		return;
	}
	
	if (this->GetAvailability()) { // no target, no moving
		drone.Update(dt, scheduler); // try to initialize drone route
		if (!(this->GetAvailability())) { // if successful (results in 1 move)
			charge -= dt;
			double totalDist = 0;
			IEntity* robot = drone->RetNearestEntity();
			totalDist += this->GetPosition().Distance(this->GetDestination());
			totalDist += this->GetDestination().Distance(robot->GetDestination());
			//  total_dist += robot->GetDestination.Distance(nearestRecharge->GetPosition()); // relies on nearestRecharge, not fully implemented yet
			if ((total_dist / speed) > (charge)) { // (DOUBLE CHECK MATH) if traveling total distance requires more time moving than the charge holds
				rechargeStrategy = new BeelineStrategy(this->GetPosition(), nearestRecharge->GetPosition());
			}
		}
	}
	else if (rechargeStrategy) { // pathing to recharge. deleted and NULL when completed
		// move to nearestRecharge, recalc if the station is mobile
		if (nearIsMobile) {
			// recalc then move
		}
		else {
			rechargeStrategy->Move(this, dt);
		}
	}
	else {
		drone.Update(dt, scheduler);
		charge -= dt;
	}
	
=======
>>>>>>> 7516781c84c973007bde2847755185549e587f03
} 
