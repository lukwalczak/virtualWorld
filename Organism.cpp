#include "Organism.h"
Organism::Organism(World *world): world(world) {}
Organism::~Organism(){
  this->world = nullptr;
}
const int Organism::getInitiative() const { return this->initiative; }
const int Organism::getStrenght() const { return this->strength; }
const int Organism::getPosX() const { return this->posX; }
const int Organism::getPosY() const { return this->posY; }
const int Organism::getAge() const { return this->age; }
const char Organism::getOrganismChar() const { return this->organismChar; }
void Organism::kill() {
  this->world = nullptr;
}
