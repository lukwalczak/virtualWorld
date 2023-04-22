#include "Human.h"
#include "config.h"

Human::Human(int strength, int initiative, int posX, int posY, char organismChar, World &world) : 
  Animal(strength, initiative, posX, posY, organismChar, world), abilityCooldown(0), abilityLastTime(0) {}
Human::~Human(){}
int Human::action(int dx, int dy){
  if(dx && this->posX + dx >= 1 && this->posX + dx <= WORLDWIDTH){
    this->posX += dx;
    this->age++;
    return 1;
  }
  if(dy && this->posY + dy >= 1 && this->posY + dy <= WORLDHEIGHT){
    this->posY += dy;
    this->age++;
    return 1;
  }
  return 0;
}
