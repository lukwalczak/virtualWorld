#pragma once
#include "../Animal.h"

class Wolf : public Animal {
public:
  Wolf(int strength, int initiative, int posX, int posY, char organismChar, std::string fullOrganismName, World &world) :
    Animal(strength, initiative, posX, posY, organismChar, fullOrganismName, world) {};
  ~Wolf(){}
};
