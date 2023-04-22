#include "Animal.h"
#include "config.h"
#include "ncurses.h"
#include <iostream>
#include <string.h>
#include "Organism.h"
#include "World.h"

Animal::Animal(int strength, int initiative, int posX, int posY,
               char organismChar, World &world) : Organism(world) {
  this->strength = strength;
  this->initiative = initiative;
  this->posX = posX;
  this->posY = posY;
  this->age = 0;
  this->organismChar = organismChar;
}

Animal::~Animal(){}

void Animal::action() {
  // go up/down if direction is 1 otherwise left/right
  bool moved = false;
  int dx = 0;
  int dy = 0;
  this->age++;
  while (!moved) {
    
    int direction = rand() % 2;
    
    if (direction && (this->posY - 1 >= 1 || this->posY + 1 <= WORLDHEIGHT)) {
      direction = rand() % 2;
      // 1 go up 0 go down
      if (direction && this->posY - 1 >= 1) {
        dy--;
        moved = true;
      } else {
        dy++;
        moved = true;
      }
    }

    if (!direction && (this->posX - 1 >= 1 || this->posX + 1 <= WORLDWIDTH)) {
      //1 go left 0 go right
      direction = rand() % 2;
      if(direction && this->posX - 1 >= 1){
        dx--;
        moved = true;
      }else{
        dx++;
        moved = true;
      }

    }
  }

  Organism *collidingOrganism = this->world.getOrganismAtXY(this->posX+dx,this->posY+dy);
  if(collidingOrganism == nullptr || this->collision(collidingOrganism)){
    this->posX += dx;
    this->posY += dy;
  }

  collidingOrganism = nullptr;
  delete collidingOrganism;
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

bool Animal::fight(Organism *colidingOrganism){
  if(this->strength >= colidingOrganism->getStrenght()){
    if(dynamic_cast<Human*>(colidingOrganism) != nullptr){
      if(dynamic_cast<Human*>(colidingOrganism)->getAbilityLastTime() > 0){
        return 0;
      }
    }
    colidingOrganism->kill();
    this->world.removeOrganism(colidingOrganism);
    return 1;
  }else{
    this->kill();
    this->world.removeOrganism(this);
    return 0;
  }

}

void Animal::draw() const {
  mvprintw(this->posX, this->posY, &this->organismChar);
}
