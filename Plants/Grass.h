#pragma once
#include "../Plant.h"

class Grass : public Plant {
public:
  Grass(int strength, int posX, int posY, char organismChar, std::string fullOrganismName, World &world) :
    Plant(strength, posX, posY, organismChar, fullOrganismName, world) {}
  ~Grass(){}
};
