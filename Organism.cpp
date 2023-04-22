#include "Organism.h"
#include <string>

Organism::Organism(int strength, int initiative, int posX, int posY, char organismChar, std::string fullOrganismName, World &world) :
  strength(strength), initiative(initiative), posX(posX), posY(posY),
  age(0),organismChar(organismChar), fullOrganismName(fullOrganismName), world(world) {}
Organism::~Organism(){}
const int Organism::getInitiative() const { return this->initiative; }
const int Organism::getStrenght() const { return this->strength; }
const int Organism::getPosX() const { return this->posX; }
const int Organism::getPosY() const { return this->posY; }
const int Organism::getAge() const { return this->age; }
const char Organism::getOrganismChar() const { return this->organismChar; }
const std::string Organism::getFullOrganismName() const {return this->fullOrganismName;}
bool Organism::operator<(const Organism &other) const {
  if(this->initiative < other.getInitiative()){
    return true;
  } else if( this->initiative > other.getInitiative()){
    return false;
  } else{
    if(this->age < other.getAge()){
      return true;
    }else{
      return false;
    }
  }
  
}
void Organism::kill() {
}
