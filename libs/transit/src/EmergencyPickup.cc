#include "EmergencyPickup.h"

EmergencyPickup :: EmergencyPickup(JsonObject &obj) : details(obj){
    JsonArray pos(obj["position"]);
    position = {pos[0], pos[1], pos[2]};

    JsonArray dir(obj["direction"]);
    direction = {dir[0], dir[1], dir[2]};

    speed = obj["speed"];

    available = true;

    //this->SearchDrone();
}

EmergencyPickup :: ~EmergencyPickup(){}


void EmergencyPickup :: SearchDrone(){
  for(int i = 0; i<(*entities).size(); i++){
    JsonObject detailsTemp = (*entities)[i]->GetDetails();
    std::string typeTemp = detailsTemp["type"];
    if(typeTemp.compare("drone") == 0){
      //FIXME if have error.
      droneBattery = ((*entities)[i]);
      break;
    }
  }
}


void EmergencyPickup :: Update(double dt, std::vector<IEntity*> scheduler){
    //FIXME:

    //std::cout<<"enter Update"<<std::endl;
    if(toTargetPosStrategy){
      toTargetPosStrategy->Move(this, dt);

      if(toTargetPosStrategy->IsCompleted()){
        delete toTargetPosStrategy;
        toTargetPosStrategy = NULL;
      }  
    }
    else if (toTargetDestStrategy){
        //FIXME:check if it need to pick up the drone
        toTargetDestStrategy->Move(this, dt);
        droneBattery->SetPosition(this->GetPosition());
        droneBattery->SetDirection(this->GetDirection());
        if(toTargetDestStrategy->IsCompleted()){
          delete toTargetDestStrategy;
          toTargetDestStrategy = NULL;
        }
    }
    else{
      if(pickup == false){
        //std::cout<<"may be droneBattery error"<<std::endl;
        this->SearchDrone();
        if(droneBattery -> GetEmergency()){
          //std::cout<<"droneBattery no error"<<std::endl;
          destination = droneBattery->GetPosition();
          toTargetPosStrategy = new BeelineStrategy(this->position, this->destination);
          pickup = true;
          available = false;
        }
      }
      else{
        destination = droneBattery->GetDestination();
        toTargetDestStrategy = new BeelineStrategy(this->position, this->destination);
          pickup = false;
          available = true;
      }
    }
}

void EmergencyPickup::Rotate(double angle) {
  Vector3 dirTmp = direction;
  direction.x = dirTmp.x * std::cos(angle) - dirTmp.z * std::sin(angle);
  direction.z = dirTmp.x * std::sin(angle) + dirTmp.z * std::cos(angle);
}

