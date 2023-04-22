#pragma once
#include <iostream>
#include "Organism.h"
#include <vector>
#include "Human.h"
class Organism;
class World {
private:
  std::vector<Organism*> organisms;
  Human *human;
  int width;
  int height;
public:
  World();
  ~World();
  void firstActionTurn();
  void secondActionTurn();
  void draw();
  Human *getHuman();
  void generateNewWorld();
  Organism *getOrganismAtXY(int x, int y);
  void removeOrganism(Organism *organism);
};
