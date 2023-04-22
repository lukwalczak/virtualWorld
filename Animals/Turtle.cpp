#include "Turtle.h"

Turtle::Turtle(int strength, int initiative, int posX, int posY, char organismChar, std::string fullOrganismName, World &world) :
    Animal(strength, initiative, posX, posY, organismChar, fullOrganismName, world) {};

Turtle::~Turtle(){}

void Turtle::action(){
  if(rand () % 4 == 0){
    Animal::action();
    return;
  }
  this->age++;
  return;
}
