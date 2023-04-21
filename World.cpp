#include "World.h"
#include "Console.h"
#include "config.h"
#include "Animals/Wolf.h"

World::World() {
  this->width = WORLDWIDTH;
  this->height = WORLDHEIGHT;
  this->human = new Human(HUMANSTR, HUMANINITIATIVE, HUMANSTARTINGX, HUMANSTARTINGY, HUMANCHAR, *this);
  this->organisms.push_back(this->human);
  this->generateNewWorld();
}
World::~World() {}

Human *World::getHuman() { return this->human; }

void World::draw() {
  for(Organism* o : this->organisms){
    o->draw();
  }
}

void World::generateNewWorld(){
  int randX = rand() % WORLDWIDTH + 1;
  int randY = rand() % WORLDHEIGHT + 1;
  Wolf *w = new Wolf(WOLFSTR, WOLFINITIATIVE, randX, randY, WOLFCHAR, *this);
  this->organisms.push_back(w);
}

void World::firstActionTurn() {
  for(Organism* o : this->organisms){
    if(dynamic_cast<Human*>(o) == nullptr){
      if(o->getInitiative() > HUMANINITIATIVE || ( o->getInitiative() == HUMANINITIATIVE && o->getAge() > this->human->getAge())){
        o->action();
      }
    }
  }
}

void World::secondActionTurn(){
  for(Organism* o : this->organisms){
    if(dynamic_cast<Human*>(o) == nullptr){
      if(o->getInitiative() < HUMANINITIATIVE || ( o->getInitiative() == HUMANINITIATIVE && o->getAge() <= this->human->getAge())){
        o->action();
      }
    }
  }
}
