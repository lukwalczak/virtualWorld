#pragma once
#include "Organism.h"

class Animal : public Organism {
public:
  Animal(int strenght, int initiative, int posX, int posY, char organismChar);
  virtual void collision() override;
  virtual void action() override;
  virtual void draw() const override;
};
