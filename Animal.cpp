#include "Animal.h"
#include "config.h"
#include "ncurses.h"
#include <iostream>
#include <string.h>
#include "Organism.h"
#include "World.h"

Animal::Animal(int strength, int initiative, int posX, int posY,
               char organismChar, World *world) : Organism(world) {
  this->strength = strength;
  this->initiative = initiative;
  this->posX = posX;
  this->posY = posY;
  this->age = 0;
  this->organismChar = organismChar;
}

void Animal::action() {
  // go up/down if direction is 1 otherwise left/right
  bool moved = false;
  int dx = 0;
  int dy = 0;
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

  Organism *colidingOrganism = this->world->getOrganismAtXY(this->posX+dx,this->posY+dy);
  if(colidingOrganism == nullptr){
    this->posX += dx;
    this->posY += dy;
    return;
  }
  this->collision(colidingOrganism);

}

void Animal::collision(Organism *colidingOrganism) {  
  
  if(this->getOrganismChar() == colidingOrganism->getOrganismChar()){
    this->breed();
    return;
  }

  this->fight(colidingOrganism);
  return;

}

void Animal::breed() const {}

void Animal::fight(Organism *colidingOrganism){
  if(this->strength >= colidingOrganism->getStrenght()){
    colidingOrganism->kill();
    this->world->removeOrganism(colidingOrganism);
  }else{
    this->kill();
    this->world->removeOrganism(this);
  }

}

void Animal::draw() const {
  mvprintw(this->posX, this->posY, &this->organismChar);
}
