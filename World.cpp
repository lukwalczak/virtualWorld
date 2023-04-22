#include "World.h"
#include "Console.h"
#include "config.h"
#include "Animals/Wolf.h"
#include <algorithm>

World::World() {
  this->width = WORLDWIDTH;
  this->height = WORLDHEIGHT;
  this->generateNewWorld();
}
World::~World() {
  for(Organism *o: this->organisms){
    o = nullptr;
    delete o;
  }
}

Human *World::getHuman() { return this->human; }

bool World::isHumanAlive() const { 
  if(this->human != nullptr)
    return true;
  return false;

}

void World::draw() {
  for(Organism* o : this->organisms){
    o->draw();
  }
}

void World::generateNewWorld(){
  this->human = new Human(HUMANSTR, HUMANINITIATIVE, HUMANSTARTINGX, HUMANSTARTINGY, HUMANCHAR, HUMANFULLNAME, *this);
  this->organisms.push_back(this->human);
  
  int randX = rand() % WORLDWIDTH + 1;
  int randY = rand() % WORLDHEIGHT + 1;
  Wolf *w = new Wolf(WOLFSTR, WOLFINITIATIVE, randX, randY, WOLFCHAR, WOLFFULLNAME, *this);
  this->organisms.push_back(w);
}

// turn of animals that have greater initiative than human
void World::firstActionTurn() {
  for(Organism* o : this->organisms){
    if(dynamic_cast<Human*>(o) == nullptr){
      if(o->getInitiative() > HUMANINITIATIVE || ( o->getInitiative() == HUMANINITIATIVE && o->getAge() > this->human->getAge())){
        o->action();
      }
    }
  }
}

//turn of animals that have less initiative than human
void World::secondActionTurn(){
  for(Organism *o : this->organisms){
    if(dynamic_cast<Human*>(o) == nullptr){
      if(o->getInitiative() < HUMANINITIATIVE || ( o->getInitiative() == HUMANINITIATIVE && o->getAge() <= this->human->getAge())){
        o->action();
      }
    }
  }
}

Organism *World::getOrganismAtXY(int x, int y){
  for(Organism *o : this->organisms){
    if(o->getPosX() == x && o->getPosY() == y){
      return o;
    }
  }
  return nullptr;
}

void World::removeOrganism(Organism *organism){
  this->organisms.erase(std::remove(this->organisms.begin(), this->organisms.end(), organism), this->organisms.end());
  if(dynamic_cast<Human*>(organism) != nullptr){
    this->human = nullptr;
  }
}

void World::addLog(std::string log){
  this->logs.insert(this->logs.begin(), log);
}

std::vector<std::string> World::getLogs(){
  return this->logs;
}

std::vector<std::string> World::getLastLogs(){
  if(this->logs.size() <= 32)
    return this->logs;
  std::vector<std::string>::const_iterator first = this->logs.begin();
  std::vector<std::string>::const_iterator last = this->logs.begin() + 32;
  std::vector<std::string> lastLogs(first, last);
  return lastLogs;
}
