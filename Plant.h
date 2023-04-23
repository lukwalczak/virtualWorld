#pragma once
#include "Organism.h"

class Plant : public Organism{
public:
  Plant(int strenght, int posX, int posY, char organismChar, std::string fullOrganismName, World &world);
  virtual ~Plant();
  void action() override;
  void addBreedingLog(Organism *newOrganism);
};
