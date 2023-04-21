#include "Organism.h"

Organism::Organism(World &world): world(world) {}
const int Organism::getInitiative() const { return this->initiative; }
const int Organism::getStrenght() const { return this->strength; }
const int Organism::getPosX() const { return this->posX; }
const int Organism::getPosY() const { return this->posY; }
const int Organism::getAge() const { return this->age; }
