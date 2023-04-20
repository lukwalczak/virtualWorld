#include "Animal.h"
#include "ncurses.h"
#include <string.h>
#include <iostream>

Animal::Animal(int strength, int initiative, int posX, int posY, char organismChar){
  this->strength = strength;
  this->initiative = initiative;
  this->posX = posX;
  this->posY = posY;
  this->organismChar = organismChar;
}

void Animal::action(){

}

void Animal::collision(){

}

void Animal::draw() const {
  mvprintw(this->posX, this->posY, &this->organismChar );
}
