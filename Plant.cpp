#include "Plant.h"
#include "Organism.h"
#include "World.h"
#include <string>
#include "OrganismFactory.h"

Plant::Plant(int strength, int posX, int posY, char organismChar, std::string fullOrganismName, World &world) :
  Organism(strength, 0, posX, posY, organismChar, fullOrganismName, world){}
Plant::~Plant(){}
void Plant::action(){
  int chance = rand() % 20;
  if(chance == 0){
  for(int i = -1; i <= 1; i+=2){
    if(this->world.getOrganismAtXY(this->posX + i, this->posY) == nullptr && this->checkMove(i,0)){
      Organism *o = OrganismFactory::createOrganism(this->getFullOrganismName(), this->posX + i, this->posY, this->world);
      this->world.addOrganism(o);
      this->addBreedingLog(o);
      return;
    }
    if(this->world.getOrganismAtXY(this->posX, this->posY + i) == nullptr && this->checkMove(0, i)){
      Organism *o = OrganismFactory::createOrganism(this->getFullOrganismName(), this->posX, this->posY + i, this->world);
      this->world.addOrganism(o);
      this->addBreedingLog(o);
      return;
    }
  }
  }
}

void Plant::addBreedingLog(Organism *newOrganism){
  std::string log;
  log = newOrganism->getFullOrganismName() + " has been planted";
  this->world.addLog(log);
}
