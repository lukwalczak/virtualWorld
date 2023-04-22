#pragma once
#include "../Plant.h"

class Guarana : public Plant {
public:
  Guarana(int strength, int posX, int posY, char organismChar, std::string fullOrganismName, World &world) :
    Plant(strength, posX, posY, organismChar, fullOrganismName, world) {}
  ~Guarana(){}
  bool collision(Organism *collidingOrganism) override;
  void addGuaranaLog(Organism *collidingOrganism);
};
