#include "Organism.h"
#include <string>
#include "ncurses.h"
#include "World.h"
#include "config.h"
Organism::Organism(int strength, int initiative, int posX, int posY, char organismChar, std::string fullOrganismName, World &world) :
  strength(strength), initiative(initiative), posX(posX), posY(posY),
  age(0), breedCooldown(0),organismChar(organismChar), fullOrganismName(fullOrganismName), world(world) {}
Organism::~Organism(){}
const int Organism::getInitiative() const { return this->initiative; }
const int Organism::getStrenght() const { return this->strength; }
const int Organism::getPosX() const { return this->posX; }
const int Organism::getPosY() const { return this->posY; }
const int Organism::getAge() const { return this->age; }
const int Organism::getBreedCooldown() const { return this->breedCooldown; }
const char Organism::getOrganismChar() const { return this->organismChar; }
const std::string Organism::getFullOrganismName() const {return this->fullOrganismName;}
void Organism::setBreedCooldown(){
  this->breedCooldown = BREEDCOOLDOWN;
}
void Organism::draw() const {
  std::string temp(1,this->organismChar);
  mvprintw(this->posY, this->posX, temp.c_str());
}
bool Organism::checkMove(int dx, int dy) const {
  if(dx && this->posX + dx >= 1 && this->posX + dx <= this->world.getWidth()){
    return 1;
  }
  if(dy && this->posY + dy >= 1 && this->posY + dy <= this->world.getHeight()){
    return 1;
  }
  return 0;
}
bool Organism::collision(Organism *colidingOrganism){
  return false;
}
bool Organism::checkAdjacentFreeSpaces() const {
  for(int i = -1; i <= 1; i+=2){
    if(this->world.getOrganismAtXY(this->posX + i, this->posY) == nullptr){
      return true;
    }  
  }
  for(int i = -1; i <= 1; i+=2){
    if(this->world.getOrganismAtXY(this->posX, this->posY + i) == nullptr){
      return true;
    }  
  }
  return false;
}
