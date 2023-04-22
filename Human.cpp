#include "Human.h"
#include "config.h"
#include "World.h"

Human::Human(int strength, int initiative, int posX, int posY, char organismChar, World &world) : 
  Animal(strength, initiative, posX, posY, organismChar, world), abilityCooldown(0), abilityLastTime(0) {}

Human::~Human(){}

int Human::action(int dx, int dy){

  if(this->checkMove(dx,dy)){
    
    Organism *collidingOrganism = this->world.getOrganismAtXY(this->posX + dx, this->posY);
    
    if(collidingOrganism == nullptr || this->collision(collidingOrganism)){
      this->posX += dx;
      this->age++;
      this->deincrementAbilityLastTime();
      collidingOrganism = nullptr;
      delete collidingOrganism;
      return 1;
    } else if(this->abilityLastTime > 0){
      this->moveToAdjacent(); 
      return 1;
    } else {
      return 1;
    }

  }
  
  if(this->checkMove(dx,dy)){
    
    Organism *collidingOrganism = this->world.getOrganismAtXY(this->posX, this->posY + dy);
    
    if(collidingOrganism == nullptr || this->collision(collidingOrganism)){
      this->posY += dy;
      this->age++;
      this->deincrementAbilityLastTime();
      collidingOrganism = nullptr;
      delete collidingOrganism;
      return 1;
    } else if(this->abilityLastTime > 0){
      this->moveToAdjacent();
      return 1;
    }else{
      return 1;
    }

  }
  
  return 0;
}

bool Human::collision(Organism *collidingOrganism){
  if(this->fight(collidingOrganism)){
    return true;
  }
  return false;
}

bool Human::fight(Organism *collidingOrganism){
  if(this->strength >= collidingOrganism->getStrenght()){
    collidingOrganism->kill();
    this->world.removeOrganism(collidingOrganism);
    return true;
  } else {
    if(this->abilityLastTime > 0){
      return false;
    } else {
      this->kill();
      this->world.removeOrganism(this);
      return false;
    }
  }
}

const int Human::getAbilityLastTime() const { return this->abilityLastTime; }

bool Human::useAbility() {
  if(this->abilityCooldown == 0){
    this->abilityLastTime = 5; 
    return 1;
  }
  return 0;
}

void Human::deincrementAbilityLastTime() {
  if(this->abilityLastTime > 0){
    this->abilityLastTime--;
    this->abilityCooldown = 5;
  }else if(this->abilityCooldown > 0){
    this->abilityCooldown--;
  }
}

bool Human::checkMove(int dx, int dy){
  if(dx && this->posX + dx >= 1 && this->posX + dx <= WORLDWIDTH){
    return 1;
  }
  if(dy && this->posY + dy >= 1 && this->posY + dy <= WORLDHEIGHT){
    return 1;
  }
  return 0;
}

void Human::moveToAdjacent(){
  for(int i = -1; i <= 1; i++){
    if(this->world.getOrganismAtXY(this->posX + i, this->posY) == nullptr && this->checkMove(i,0)){
      this->posX += i;
      return;
    }
    if(this->world.getOrganismAtXY(this->posX, this->posY + i) == nullptr && this->checkMove(0, i)){
      this->posY += i;
      return;
    }
  }

}
