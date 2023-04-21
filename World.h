#pragma once
#include <iostream>
#include "Organism.h"
#include <vector>
#include "Human.h"

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
};
