#include "Plant.h"
#include "Organism.h"
#include "World.h"
#include <string>

Plant::Plant(int strength, int posX, int posY, char organismChar, std::string fullOrganismName, World &world) :
  Organism(strength, 0, posX, posY, organismChar, fullOrganismName, world){}
Plant::~Plant(){}
void Plant::action(){
  for(int i = -1; i <= 1; i++){
    if(this->world.getOrganismAtXY(this->posX + i, this->posY) == nullptr && this->checkMove(i,0)){
      //TODO ROZMNAZANIE
      return;
    }
    if(this->world.getOrganismAtXY(this->posX, this->posY + i) == nullptr && this->checkMove(0, i)){
      //TODO ROZMNAZANIE
      return;
    }
  }
}
