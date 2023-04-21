#include "Animal.h"
#include "config.h"
#include "ncurses.h"
#include <iostream>
#include <string.h>

Animal::Animal(int strength, int initiative, int posX, int posY,
               char organismChar, World &world) : Organism(world) {
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
  while (!moved) {
    
    int direction = rand() % 2;
    
    if (direction && (this->posY - 1 >= 1 || this->posY + 1 <= WORLDHEIGHT)) {
      direction = rand() % 2;
      // 1 go up 0 go down
      if (direction && this->posY - 1 >= 1) {
        this->posY--;
        moved = true;
      } else {
        this->posY++;
        moved = true;
      }
    }

    if (!direction && (this->posX - 1 >= 1 || this->posX + 1 <= WORLDWIDTH)) {
      //1 go left 0 go right
      direction = rand() % 2;
      if(direction && this->posX - 1 >= 1){
        this->posX--;
        moved = true;
      }else{
        this->posX++;
        moved = true;
      }

    }
  }
}

void Animal::collision() {}

void Animal::draw() const {
  mvprintw(this->posX, this->posY, &this->organismChar);
}
