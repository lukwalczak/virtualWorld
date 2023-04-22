#include "World.h"
#include "Animals/Animals.h"
#include "Console.h"
#include "config.h"
#include <algorithm>

World::World(int &gameTurn) : gameTurn(gameTurn) {
  this->width = WORLDWIDTH;
  this->height = WORLDHEIGHT;
}
World::~World() {
  for (Organism *o : this->organisms) {
    delete o;
  }
  this->organisms.clear();
  this->logs.clear();
}

Human *World::getHuman() { return this->human; }

bool World::isHumanAlive() const {
  if (this->human != nullptr)
    return true;
  return false;
}

void World::draw() {
  for (Organism *o : this->organisms) {
    o->draw();
  }
}

void World::clearWorld(){
  for (Organism *o : this->organisms) {
    delete o;
  }
  this->organisms.clear();
  this->logs.clear();
}

void World::generateNewWorld() {
  this->clearWorld(); 
  this->human = new Human(HUMANSTR, HUMANINITIATIVE, HUMANSTARTINGX,
                          HUMANSTARTINGY, HUMANCHAR, HUMANFULLNAME, *this);
  this->organisms.push_back(this->human);
  this->generateAnimals();
}

void World::generateAnimals() {
  int randX = rand() % WORLDWIDTH + 1;
  int randY = rand() % WORLDHEIGHT + 1;
  for (int i = 0; i < (rand() % 3) + 1; i++) {
    while (this->getOrganismAtXY(randX, randY) != nullptr) {
      randX = rand() % WORLDWIDTH + 1;
      randY = rand() % WORLDHEIGHT + 1;
    }
    Wolf *a = new Wolf(WOLFSTR, WOLFINITIATIVE, randX, randY, WOLFCHAR,
                       WOLFFULLNAME, *this);
    this->organisms.push_back(a);
  }
  for (int i = 0; i < (rand() % 3) + 1; i++) {
    while (this->getOrganismAtXY(randX, randY) != nullptr) {
      randX = rand() % WORLDWIDTH + 1;
      randY = rand() % WORLDHEIGHT + 1;
    }
    Sheep *a = new Sheep(SHEEPSTR, SHEEPINITIATIVE, randX, randY, SHEEPCHAR,
                         SHEEPFULLNAME, *this);
    this->organisms.push_back(a);
  }
  for (int i = 0; i < (rand() % 3) + 1; i++) {
    while (this->getOrganismAtXY(randX, randY) != nullptr) {
      randX = rand() % WORLDWIDTH + 1;
      randY = rand() % WORLDHEIGHT + 1;
    }
    Antelope *a = new Antelope(ANTELOPESTR, ANTELOPEINITIATIVE, randX, randY,
                               ANTELOPECHAR, ANTELOPEFULLNAME, *this);
    this->organisms.push_back(a);
  }
  for (int i = 0; i < (rand() % 3) + 1; i++) {
    while (this->getOrganismAtXY(randX, randY) != nullptr) {
      randX = rand() % WORLDWIDTH + 1;
      randY = rand() % WORLDHEIGHT + 1;
    }
    Fox *a = new Fox(FOXSTR, FOXINITIATIVE, randX, randY, FOXCHAR, FOXFULLNAME,
                     *this);
    this->organisms.push_back(a);
  }
  for (int i = 0; i < (rand() % 3) + 1; i++) {
    while (this->getOrganismAtXY(randX, randY) != nullptr) {
      randX = rand() % WORLDWIDTH + 1;
      randY = rand() % WORLDHEIGHT + 1;
    }
    Turtle *a = new Turtle(TURTLESTR, TURTLEINITIATIVE, randX, randY,
                           TURTLECHAR, TURTLEFULLNAME, *this);
    this->organisms.push_back(a);
  }
}

// turn of animals that have greater initiative than human
void World::firstActionTurn() {
  for (Organism *o : this->organisms) {
    if (dynamic_cast<Human *>(o) == nullptr) {
      if (o->getInitiative() > HUMANINITIATIVE || ( o->getInitiative() == HUMANINITIATIVE && this->isHumanAlive() && o->getAge() > this->human->getAge())) {
        o->action();
      }
    }
  }
}

// turn of animals that have less initiative than human
void World::turn() {
  for (Organism *o : this->organisms) {
    if (dynamic_cast<Human *>(o) == nullptr) {
      if (o->getInitiative() < HUMANINITIATIVE || ( o->getInitiative() == HUMANINITIATIVE && this->isHumanAlive() && o->getAge() <= this->human->getAge())) {
        o->action();
      }
    }
  }
}

bool World::compareOrganisms(Organism *o1, Organism *o2){
  if(o1->getInitiative() > o2->getInitiative()){
    return true;
  }else if( o1->getInitiative() < o2->getInitiative()){
    return false;
  }else{
    if(o1->getAge() > o2->getAge()){
      return true;
    }else{
      return false;
    }
  }
}

void World::sortOrganisms() {
  std::sort(this->organisms.begin(), this->organisms.end(), this->compareOrganisms);
}

Organism *World::getOrganismAtXY(int x, int y) {
  for (Organism *o : this->organisms) {
    if (o->getPosX() == x && o->getPosY() == y) {
      return o;
    }
  }
  return nullptr;
}

void World::removeOrganism(Organism *organism) {
  if (dynamic_cast<Human *>(organism) != nullptr) {
    this->human = nullptr;
  }
  this->organisms.erase(
      std::remove(this->organisms.begin(), this->organisms.end(), organism),
      this->organisms.end()); 
}

void World::startTurn() {
  this->sortOrganisms();
  this->addLog("-----------------");
  std::string log = "Start of turn: " + std::to_string(this->gameTurn);
  this->addLog(log);
}

void World::endTurn() {
  std::string log = "End of turn: " + std::to_string(this->gameTurn);
  this->addLog(log);
}

void World::addLog(std::string log) {
  this->logs.insert(this->logs.begin(), log);
}

std::vector<std::string> World::getLogs() { return this->logs; }

std::vector<std::string> World::getLastLogs() {
  if (this->logs.size() <= 32)
    return this->logs;
  std::vector<std::string>::const_iterator first = this->logs.begin();
  std::vector<std::string>::const_iterator last = this->logs.begin() + 32;
  std::vector<std::string> lastLogs(first, last);
  return lastLogs;
}
