#include "Antelope.h"

void Antelope::action(){
  Animal::action();
  Animal::action();
}

bool Antelope::didReflect(Organism *attackingOrganism){
  int r = rand() % 4;
  if(r == 0){
    return false;
  }
  this->addEscapeLog(attackingOrganism);
  return true;
}
