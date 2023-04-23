#include "Human.h"
#include "config.h"
#include "World.h"
#include "Plant.h"

Human::Human(int strength, int initiative, int posX, int posY, char organismChar, std::string fullOrganismName, World &world) : 
  Animal(strength, initiative, posX, posY, organismChar, fullOrganismName, world), abilityCooldown(0), abilityLastTime(0) {}

Human::~Human(){}

int Human::action(int dy, int dx){
  int startingX = this->posX, startingY = this->posY;
  if(dx && this->posX + dx >= 1 && this->posX + dx <= WORLDWIDTH){
    
    Organism *collidingOrganism = this->world.getOrganismAtXY(this->posX + dx, this->posY);
    if(collidingOrganism == nullptr || this->collision(collidingOrganism)){
      this->move(dx, dy);
      this->age++;
      this->deincrementAbilityLastTime();
      collidingOrganism = nullptr;
      delete collidingOrganism;
      return 1;
    } else if(this->abilityLastTime > 0){
      this->moveToAdjacent();
      this->age++;
      return 1;
    } else {
      return 1;
    }

  }
  
  if(dy && this->posY + dy >= 1 && this->posY + dy <= WORLDHEIGHT){
    
    Organism *collidingOrganism = this->world.getOrganismAtXY(this->posX, this->posY + dy);
    if(collidingOrganism == nullptr || this->collision(collidingOrganism)){
      this->move(dx,dy);
      this->age++;
      this->deincrementAbilityLastTime();
      collidingOrganism = nullptr;
      delete collidingOrganism;
      return 1;
    } else if(this->abilityLastTime > 0){
      this->moveToAdjacent();
      this->age++;
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
    if(dynamic_cast<Animal*>(collidingOrganism) != nullptr && dynamic_cast<Animal*>(collidingOrganism)->didReflect(this)){
      this->addReflectionLog(collidingOrganism); 
      return false;
    }
    if(dynamic_cast<Plant*>(collidingOrganism) != nullptr){
      dynamic_cast<Plant*>(collidingOrganism)->collision(this);
    }
    this->addFightLog(collidingOrganism, true);
    this->world.removeOrganism(collidingOrganism);
    return true;
  } else {
    if(this->abilityLastTime > 0){
      return false;
    } else {
      this->addFightLog(collidingOrganism, false);
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

void Human::moveToAdjacent(){
  for(int i = -1; i <= 1; i++){
    if(this->world.getOrganismAtXY(this->posX + i, this->posY) == nullptr && this->checkMove(i,0)){
      this->move(i,0);
      return;
    }
    if(this->world.getOrganismAtXY(this->posX, this->posY + i) == nullptr && this->checkMove(0, i)){
      this->move(0,i);
      return;
    }
  }

}
