#include "World.h"
#include "Animals/Animals.h"
#include "Console.h"
#include "config.h"
#include <algorithm>

World::World() {
  this->width = WORLDWIDTH;
  this->height = WORLDHEIGHT;
}
World::~World() {
  for (Organism *o : this->organisms) {
    o = nullptr;
    delete o;
  }
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

void World::generateNewWorld() {
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
      if (o->getInitiative() > HUMANINITIATIVE ||
          (o->getInitiative() == HUMANINITIATIVE &&
           o->getAge() > this->human->getAge())) {
        o->action();
      }
    }
  }
}

// turn of animals that have less initiative than human
void World::turn() {
  for (Organism *o : this->organisms) {
    if (dynamic_cast<Human *>(o) == nullptr) {
      o->action();
    }
  }
}

void World::sortOrganisms() {}

Organism *World::getOrganismAtXY(int x, int y) {
  for (Organism *o : this->organisms) {
    if (o->getPosX() == x && o->getPosY() == y) {
      return o;
    }
  }
  return nullptr;
}

void World::removeOrganism(Organism *organism) {
  this->organisms.erase(
      std::remove(this->organisms.begin(), this->organisms.end(), organism),
      this->organisms.end());
  if (dynamic_cast<Human *>(organism) != nullptr) {
    this->human = nullptr;
  }
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
