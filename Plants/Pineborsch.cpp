#include "Pineborsch.h"
#include "../World.h"
#include <string>

bool Pineborsch::collision(Organism *collidingOrganism){
  this->addPineborschLog(collidingOrganism);
  this->world.removeOrganism(collidingOrganism);
  this->world.removeOrganism(this);
  return false;
}

void Pineborsch::addPineborschLog(Organism *collidingOrganism){
  std::string log;
  log = collidingOrganism->getFullOrganismName() + " got killed by " + this->fullOrganismName;
  this->world.addLog(log);
}

void Pineborsch::action(){
  for(int i = -1; i <= 1; i+=2){
    Organism *o = this->world.getOrganismAtXY(this->posX + i, this->posY);
    if(o != nullptr){
      this->addPineborschLog(o);
      this->world.removeOrganism(o);
    }
  }
  for(int i = -1; i <= 1; i+=2){
    Organism *o = this->world.getOrganismAtXY(this->posX, this->posY + i);
    if(o != nullptr){
      this->addPineborschLog(o);
      this->world.removeOrganism(o);
    }
  }
}
