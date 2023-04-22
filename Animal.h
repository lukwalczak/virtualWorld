#pragma once
#include "Organism.h"

class Animal : public Organism {
public:
  Animal(int strenght, int initiative, int posX, int posY, char organismChar, World &world);
  virtual ~Animal();
  virtual void collision(Organism *colidingOrganism) override;
  virtual void action() override;
  virtual void draw() const override;
  virtual void breed() const;
  virtual void fight(Organism *colidingOrganism);
};
