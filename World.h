#pragma once
#include <iostream>
#include "Organism.h"
#include <vector>

class World{
private:
  std::vector<Organism*> organisms;
protected:
public:
  void nextTurn();
  void draw();
};
