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
  log = collidingOrganism->getFullOrganismName() + " ate " + this->fullOrganismName + " and has been killed by it";
  this->world.addLog(log);
}
