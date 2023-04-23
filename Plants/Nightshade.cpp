#include "Nightshade.h"
#include "../World.h"
#include <string>

bool Nightshade::collision(Organism *collidingOrganism){
  this->addNightshadelog(collidingOrganism);
  this->world.removeOrganism(collidingOrganism);
  this->world.removeOrganism(this);
  return false;
}

void Nightshade::addNightshadelog(Organism *collidingOrganism){
  std::string log;
  log = collidingOrganism->getFullOrganismName() + " ate " + this->fullOrganismName + " and has been poisoned";
  this->world.addLog(log);
}
