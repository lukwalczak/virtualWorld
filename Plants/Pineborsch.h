#pragma once
#include "../Plant.h"

class Pineborsch : public Plant {
public:
  Pineborsch(int strength, int posX, int posY, char organismChar, std::string fullOrganismName, World &world) :
    Plant(strength, posX, posY, organismChar, fullOrganismName, world) {}
  ~Pineborsch(){}
};
