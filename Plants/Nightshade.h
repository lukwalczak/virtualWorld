#pragma once
#include "../Plant.h"

class Nightshade : public Plant {
public:
  Nightshade(int strength, int posX, int posY, char organismChar, std::string fullOrganismName, World &world) :
    Plant(strength, posX, posY, organismChar, fullOrganismName, world) {}
  ~Nightshade(){}
  bool collision(Organism *collidingOrganism) override;
  void addNightshadelog(Organism *collidingOrganism);  
};
