#pragma once
#include <iostream>
#include "Organism.h"
#include <vector>

class World{
private:
  std::vector<Organism*> organisms;
  int width;
  int height;
public:
  World();
  ~World();
  void nextTurn();
  void draw();
};
