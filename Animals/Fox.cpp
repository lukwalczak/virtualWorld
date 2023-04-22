#include "Fox.h"
#include "../config.h"
#include "../World.h"

Fox::Fox(int strength, int initiative, int posX, int posY, char organismChar,
         std::string fullOrganismName, World &world)
    : Animal(strength, initiative, posX, posY, organismChar, fullOrganismName,
             world){};

Fox::~Fox() {}

void Fox::action() {
  // go up/down if direction is 1 otherwise left/right
  bool moved = false;
  int dx = 0;
  int dy = 0;
  this->age++;
  Organism *collidingOrganism = nullptr;
  while (!moved) {

    int direction = rand() % 2;

    if (direction && (this->posY - 1 >= 1 || this->posY + 1 <= WORLDHEIGHT)) {
      direction = rand() % 2;
      // 1 go up 0 go down
      if (direction && this->posY - 1 >= 1) {
        collidingOrganism = this->world.getOrganismAtXY(this->posX, this->posY - 1);
        if(collidingOrganism == nullptr || this->strength >= collidingOrganism->getStrenght()){
          dy--;
          moved = true;
        }
      } else if (this->posY + 1 <= WORLDHEIGHT) { 
        collidingOrganism = this->world.getOrganismAtXY(this->posX, this->posY + 1);
        if(collidingOrganism == nullptr || this->strength >= collidingOrganism->getStrenght()){
          dy++;
          moved = true;
        }
      }
    }

    if (!direction && (this->posX - 1 >= 1 || this->posX + 1 <= WORLDWIDTH)) {
      // 1 go left 0 go right
      direction = rand() % 2;
      if (direction && this->posX - 1 >= 1) { 
        collidingOrganism = this->world.getOrganismAtXY(this->posX - 1, this->posY);
        if(collidingOrganism == nullptr || this->strength >= collidingOrganism->getStrenght()){
          dx--;
          moved = true;
        }
      } else if (this->posX <= WORLDWIDTH) {
        collidingOrganism = this->world.getOrganismAtXY(this->posX + 1, this->posY);
        if(collidingOrganism == nullptr || this->strength >= collidingOrganism->getStrenght()){
          dx++;
          moved = true;
        }
      }
    }
  }
  
  if(collidingOrganism == nullptr){
    this->move(dx, dy);
  } else if(this->collision(collidingOrganism)){
    this->move(dx, dy);
  }

  collidingOrganism = nullptr;
  delete collidingOrganism;
  return;
}
