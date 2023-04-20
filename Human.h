#pragma once
#include "Animal.h"

class Human : public Animal {
private:
  //for how long human cannot use ability again
  int abilityCooldown;
  //how long ability lasts
  int abilityLastTime;
public:
  Human(int strength, int initiative, int posX, int posY, char organismChar);
  int action(int dx, int dy);
};
