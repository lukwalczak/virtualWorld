#include "Human.h"
#include "config.h"

Human::Human(int strength, int initiative, int posX, int posY, char organismChar) : 
  Animal(strength, initiative, posX, posY, organismChar), abilityCooldown(0), abilityLastTime(0) {}

int Human::action(int dx, int dy){
  if(dx && this->posX + dx >= 1 && this->posX + dx <= WORLDWIDTH){
    this->posX += dx;
    return 1;
  }
  if(dy && this->posY + dy >= 1 && this->posY + dy <= WORLDHEIGHT){
    this->posY += dy;
    return 1;
  }
  return 0;
}
