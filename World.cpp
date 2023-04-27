#include "World.h"
#include "Animals/Animals.h"
#include "Console.h"
#include "Plants/Dandelion.h"
#include "Plants/Guarana.h"
#include "Plants/Nightshade.h"
#include "Plants/Pineborsch.h"
#include "Plants/Plants.h"
#include "config.h"
#include <algorithm>
#include "OrganismFactory.h"

World::World(int &gameTurn, int worldWidth, int worldHeight) : gameTurn(gameTurn), width(worldWidth), height(worldHeight) {
  this->logs.clear();
}
World::~World() {
  for (Organism *o : this->organisms) {
    delete o;
  }
  this->human = nullptr;
  this->organisms.clear();
  this->logs.clear();
}

Human *World::getHuman() { return this->human; }

int World::getWidth(){ return this->width; }
int World::getHeight(){ return this->height; }

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

void World::clearWorld() {
  for (Organism *o : this->organisms) {
    delete o;
  }
  this->organisms.clear();
  this->logs.clear();
  this->human = nullptr;
}

void World::generateNewWorld() {
  this->clearWorld();
  this->human = new Human(HUMANSTR, HUMANINITIATIVE, HUMANSTARTINGX,
                          HUMANSTARTINGY, HUMANCHAR, HUMANFULLNAME, *this);
  this->organisms.push_back(this->human);
  this->generateOrganisms();
}

void World::generateOrganism(std::string animalName){
  int randX = rand() % this->width + 1;
  int randY = rand() % this->height + 1;
  while(this->getOrganismAtXY(randX, randY) != nullptr) {
       randX = rand() % this->width + 1;
       randY = rand() % this->height + 1;
  }
  Organism *o = OrganismFactory::createOrganism(animalName, randX, randY, *this);
  this->organisms.push_back(o);
}

void World::generateOrganisms() {
  //generate wolfs
  for (int i = 0; i < (rand() % STARTINGWOLF) + 15; i++) {
    this->generateOrganism(WOLFFULLNAME);
  }
  

  for (int i = 0; i < (rand() % STARTINGANTELOPE); i++) {
    this->generateOrganism(ANTELOPEFULLNAME);
  }

  for (int i = 0; i < (rand() % STARTINGSHEEP); i++) {
    this->generateOrganism(SHEEPFULLNAME);
  }

  for (int i = 0; i < (rand() % STARTINGTURTLE); i++) {
    this->generateOrganism(TURTLEFULLNAME);
  }

  for (int i = 0; i < (rand() % STARTINGFOX); i++) {
    this->generateOrganism(FOXFULLNAME);
  }

  for (int i = 0; i < (rand() % STARTINGGRASS + 1); i++) {
    this->generateOrganism(GRASSFULLNAME);
  }

  for (int i = 0; i < (rand() % STARTINGDANDELION); i++) {
    this->generateOrganism(DANDELIONFULLNAME);
  }

  for (int i = 0; i < (rand() % STARTINGGUARANA); i++) {
    this->generateOrganism(GUARANAFULLNAME);
  }

  for (int i = 0; i < (rand() % STARTINGNIGHTSHADE); i++) {
    this->generateOrganism(NIGHTSHADEFULLNAME);
  }

  for (int i = 0; i < (rand() % STARTINGPINEBORSCH); i++) {
    this->generateOrganism(PINEBORSCHFULLNAME);
  }
  

}
void World::addOrganism(Organism *organism){
  if(organism != nullptr)
    this->organisms.push_back(organism);
}

// turn of animals that have greater initiative than human
void World::firstActionTurn() {
  for (Organism *o : this->organisms) {
    if (dynamic_cast<Human *>(o) == nullptr) {
      if (o->getInitiative() > HUMANINITIATIVE ||
          (o->getInitiative() == HUMANINITIATIVE && this->isHumanAlive() &&
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
      if (o->getInitiative() < HUMANINITIATIVE ||
          (o->getInitiative() == HUMANINITIATIVE && this->isHumanAlive() &&
           o->getAge() <= this->human->getAge())) {
        o->action();
      }
    }
  }
}

bool World::compareOrganisms(Organism *o1, Organism *o2) {
  if (o1->getInitiative() > o2->getInitiative()) {
    return true;
  } else if (o1->getInitiative() < o2->getInitiative()) {
    return false;
  } else {
    if (o1->getAge() > o2->getAge()) {
      return true;
    } else {
      return false;
    }
  }
}

void World::sortOrganisms() {
  std::sort(this->organisms.begin(), this->organisms.end(),
            this->compareOrganisms);
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
  if (organism == nullptr) {
    return;
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
