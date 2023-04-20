#include "World.h"
#include "Console.h"
#include "config.h"

World::World() {
  this->width = WORLDWIDTH;
  this->height = WORLDHEIGHT;
}
World::~World() {}

void World::draw() {
  Console *console = Console::getInstance();

}

void World::nextTurn() {}
