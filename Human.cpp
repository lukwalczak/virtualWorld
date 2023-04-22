#include "Human.h"
#include "config.h"
#include "World.h"

Human::Human(int strength, int initiative, int posX, int posY, char organismChar, World &world) : 
  Animal(strength, initiative, posX, posY, organismChar, world), abilityCooldown(0), abilityLastTime(0) {}

Human::~Human(){}

int Human::action(int dx, int dy){

  if(dx && this->posX + dx >= 1 && this->posX + dx <= WORLDWIDTH){
    
    Organism *collidingOrganism = this->world.getOrganismAtXY(this->posX + dx, this->posY);
    
    if(collidingOrganism == nullptr || this->collision(collidingOrganism)){
      this->posX += dx;
      this->age++;
      this->deincrementAbilityLastTime();
      collidingOrganism = nullptr;
      delete collidingOrganism;
      return 1;
    } else{
      return 1;
    }

  }
  
  if(dy && this->posY + dy >= 1 && this->posY + dy <= WORLDHEIGHT){
    
    Organism *collidingOrganism = this->world.getOrganismAtXY(this->posX, this->posY + dy);
    
    if(collidingOrganism == nullptr || this->collision(collidingOrganism)){
      this->posY += dy;
      this->age++;
      this->deincrementAbilityLastTime();
      collidingOrganism = nullptr;
      delete collidingOrganism;
      return 1;
    }else{
      return 1;
    }

  }
  
  return 0;
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
