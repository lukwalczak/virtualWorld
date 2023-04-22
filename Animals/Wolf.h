#pragma once
#include "../Animal.h"

class Wolf : public Animal {
public:
  Wolf(int strength, int initiative, int posX, int posY, char organismChar, World *world) :  Animal(strength, initiative, posX, posY, organismChar, world) {};
};
