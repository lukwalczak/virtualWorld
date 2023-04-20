#include "World.h"
#include "Console.h"
#include "config.h"

World::World() {
  this->width = WORLDWIDTH;
  this->height = WORLDHEIGHT;
  this->human = new Human(HUMANSTR, HUMANINITIATIVE, HUMANSTARTINGX, HUMANSTARTINGY, HUMANCHAR);
  this->organisms.push_back(this->human);
}
World::~World() {}

Human *World::getHuman() { return this->human; }

void World::draw() {
  for(Organism* o : this->organisms){
    o->draw();
  }
}

void World::nextTurn() {}
