#pragma once
#include "Animal.h"
class World;
class Human : public Animal {
private:
  //for how long human cannot use ability again
  int abilityCooldown;
  //how long ability lasts
  int abilityLastTime;
  void deincrementAbilityLastTime();
public:
  Human(int strength, int initiative, int posX, int posY, char organismChar, std::string fullOrganismName, World &world);
  ~Human();
  bool useAbility();
  const int getAbilityLastTime() const;
  int action(int dx, int dy);
  bool fight(Organism *collidingOrganism) override;
  bool collision(Organism *collidingOrganism) override;
  void moveToAdjacent();
};
