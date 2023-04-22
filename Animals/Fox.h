#pragma once
#include "../Animal.h"

class Fox : public Animal {
public:
  Fox(int strength, int initiative, int posX, int posY, char organismChar, std::string fullOrganismName, World &world) :
    Animal(strength, initiative, posX, posY, organismChar, fullOrganismName, world) {};
  ~Fox(){}
};