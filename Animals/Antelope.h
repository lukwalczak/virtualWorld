#pragma once
#include "../Animal.h"

class Antelope : public Animal {
public:
  Antelope(int strength, int initiative, int posX, int posY, char organismChar, std::string fullOrganismName, World &world) :
    Animal(strength, initiative, posX, posY, organismChar, fullOrganismName, world) {};
  ~Antelope(){}
  void action() override;
};
