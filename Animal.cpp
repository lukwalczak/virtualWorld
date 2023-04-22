#include "Animal.h"
#include "config.h"
#include "ncurses.h"
#include <iostream>
#include <string.h>
#include <string>
#include "Organism.h"
#include "World.h"

Animal::Animal(int strength, int initiative, int posX, int posY, char organismChar, std::string fullOrganismName, World &world) :
  Organism(strength, initiative, posX, posY, organismChar, fullOrganismName, world) {}

Animal::~Animal(){}

void Animal::action() {
  // go up/down if direction is 1 otherwise left/right
  bool moved = false;
  int dx = 0;
  int dy = 0;
  this->age++;
  while (!moved) {
    
    int direction = rand() % 2;
    
    if (direction && (this->posY - 1 >= 1 || this->posY < WORLDHEIGHT)) {
      direction = rand() % 2;
      // 1 go up 0 go down
      if (direction && this->posY - 1 >= 1) {
       dy--;
        moved = true;
      } else if(!direction && this->posY < WORLDHEIGHT ){
        dy++;
        moved = true;
      }
    }

    if (!direction && (this->posX - 1 >= 1 || this->posX  < WORLDWIDTH)) {
      //1 go left 0 go right
      direction = rand() % 2;
      if(direction && this->posX - 1 >= 1){
        dx--;
        moved = true;
      }else if(!direction && this->posX < WORLDWIDTH){
        dx++;
        moved = true;
      }

    }
  }

  Organism *collidingOrganism = this->world.getOrganismAtXY(this->posX+dx,this->posY+dy);
  if(collidingOrganism == nullptr){
    this->move(dx, dy);
  } else if(this->collision(collidingOrganism)){
    this->move(dx, dy);
  }
  return;
}

bool Animal::collision(Organism *colidingOrganism) {  

  if(this->getOrganismChar() == colidingOrganism->getOrganismChar()){
    this->breed();
    return 0;
  }

  if(this->fight(colidingOrganism)){
    return 1;
  }

  return 0;
}

void Animal::breed() const {}

bool Animal::fight(Organism *collidingOrganism){
  if(this->strength >= collidingOrganism->getStrenght()){
    if(dynamic_cast<Human*>(collidingOrganism) != nullptr){
      if(dynamic_cast<Human*>(collidingOrganism)->getAbilityLastTime() > 0){
        return 0;
      }
    }
    if(dynamic_cast<Animal*>(collidingOrganism) != nullptr && dynamic_cast<Animal*>(collidingOrganism)->didReflect(this)){
      this->addReflectionLog(collidingOrganism); 
      return 0;
    }
    this->addFightLog(collidingOrganism, true);
    collidingOrganism->kill();
    this->world.removeOrganism(collidingOrganism);
    return 1;
  }else{
    this->addFightLog(collidingOrganism, false);
    this->kill();
    this->world.removeOrganism(this);
    return 0;
  }

}

bool Animal::didReflect(Organism *attackingOrganism) { return false;}

void Animal::move(int dx, int dy){
  this->addMovedLog(dx, dy);
  this->posX += dx;
  this->posY += dy;
}

void Animal::addMovedLog(int dx, int dy){
  std::string log = this->fullOrganismName + " moved to (" + std::to_string(this->posX+dx) + "," + std::to_string(this->posY+dy) + ")";
  this->world.addLog(log); 
}

void Animal::addFightLog(Organism *collidingOrganism, bool won){
  std::string log;
  if(won){
    log = this->fullOrganismName + " killed " +
      collidingOrganism->getFullOrganismName() + " at (" +
      std::to_string(collidingOrganism->getPosX()) + "," + std::to_string(collidingOrganism->getPosY()) + ")";
  } else {
    log = this->fullOrganismName + " was killed by " +
      collidingOrganism->getFullOrganismName() + " at (" + std::to_string(this->posX) + "," + std::to_string(this->posY) + ")";
  }
  this->world.addLog(log);
}

void Animal::addReflectionLog(Organism *defendingOrganism){
  std::string log;
  log = defendingOrganism->getFullOrganismName() + " reflected " + this->getFullOrganismName() + " attack";
  this->world.addLog(log);
}
