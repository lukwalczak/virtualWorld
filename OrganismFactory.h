#pragma once
#include "Organism.h"
#include "Animals/Animals.h"
#include "Plants/Plants.h"
#include "World.h"
#include <memory>
#include "config.h"
class OrganismFactory{
public:
  OrganismFactory();
  ~OrganismFactory();
  static Organism* createOrganism(std::string name, int randX, int randY, World &world);
};
