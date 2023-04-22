#pragma once
#include "../Animal.h"

class Sheep : public Animal {
public:
  Sheep(int strength, int initiative, int posX, int posY, char organismChar, std::string fullOrganismName, World &world) :
    Animal(strength, initiative, posX, posY, organismChar, fullOrganismName, world) {};
  ~Sheep(){}
};
