#include "Guarana.h"
#include "../Animal.h"
#include "../World.h"
#include <string>

bool Guarana::collision(Organism *collidingOrganisim){
  dynamic_cast<Animal*>(collidingOrganisim)->increaseStrenght();
  this->addGuaranaLog(collidingOrganisim);
  return false;
};

void Guarana::addGuaranaLog(Organism *collidingOrganisim){
  std::string log;
  log = collidingOrganisim->getFullOrganismName() + " ate " + this->fullOrganismName + " and increased its strenght";
  this->world.addLog(log);
}

