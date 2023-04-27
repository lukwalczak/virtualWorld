#pragma once
#include "Organism.h"

class Animal : public Organism {
public:
  Animal(int strenght, int initiative, int posX, int posY, char organismChar, std::string fullOrganismName, World &world);
  virtual ~Animal();
  void increaseStrenght();
  virtual bool collision(Organism *colidingOrganism) override;
  virtual void action() override;
  virtual void breed() const;
  virtual bool fight(Organism *colidingOrganism);
  virtual bool didReflect(Organism *attackingOrganism);
  virtual void addMovedLog(int dx, int dy);
  virtual void addFightLog(Organism *collidingOrganism, bool won);
  virtual void addReflectionLog(Organism *attackingOrganism);
  virtual void addBreedingLog(Organism *newOrganism) const;
  virtual void addEscapeLog(Organism *attackingOrganism);
  virtual void move(int dx, int dy);
};
