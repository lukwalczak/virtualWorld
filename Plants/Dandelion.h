#pragma once
#include "../Plant.h"

class Dandelion : public Plant {
public:
  Dandelion(int strength, int posX, int posY, char organismChar, std::string fullOrganismName, World &world) :
    Plant(strength, posX, posY, organismChar, fullOrganismName, world) {}
  ~Dandelion(){}
  void action() override;
};
