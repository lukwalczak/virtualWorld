#include "OrganismFactory.h"
#include <memory>

OrganismFactory::OrganismFactory(){}
OrganismFactory::~OrganismFactory(){}
Organism* OrganismFactory::createOrganism(std::string name, int randX, int randY, World &world){
  Organism *ptr = nullptr;
  
  if(name == "WOLF"){
    ptr = new Wolf(WOLFSTR,WOLFINITIATIVE,randX,randY,WOLFCHAR,WOLFFULLNAME,world);
  }

  if(name == "SHEEP"){
    ptr = new Sheep(SHEEPSTR,SHEEPINITIATIVE,randX,randY,SHEEPCHAR,SHEEPFULLNAME,world);
  }
  
  if(name == "HUMAN"){
    ptr = new Human(HUMANSTR,HUMANINITIATIVE,HUMANSTARTINGX,HUMANSTARTINGY,HUMANCHAR,HUMANFULLNAME,world);
  }

  if(name == "ANTELOPE"){
    ptr = new Antelope(ANTELOPESTR,ANTELOPEINITIATIVE,randX,randY,ANTELOPECHAR,ANTELOPEFULLNAME,world);
  }

  if(name == "TURTLE"){
    ptr = new Turtle(TURTLESTR,TURTLEINITIATIVE,randX,randY,TURTLECHAR,TURTLEFULLNAME,world);
  }

  if(name == "FOX"){
    ptr = new Fox(FOXSTR,FOXINITIATIVE,randX,randY,FOXCHAR,FOXFULLNAME,world);
  }

  if(name == "GRASS"){
    ptr = new Grass(GRASSSTR,randX,randY,GRASSCHAR,GRASSFULLNAME,world);
  }

  if(name == "NIGHTSHADE"){
    ptr = new Nightshade(NIGHTSHADESTR,randX,randY,NIGHTSHADECHAR,NIGHTSHADEFULLNAME,world);
  }

  if(name == "PINEBORSCH"){
    ptr = new Pineborsch(PINEBORSCHSTR,randX,randY,PINEBORSCHCHAR,PINEBORSCHFULLNAME,world);
  }

  if(name == "GUARANA"){
    ptr = new Guarana(GUARANASTR,randX,randY,GUARANACHAR,GUARANAFULLNAME,world);
  }

  if(name == "DANDELION"){
    ptr = new Dandelion(DANDELIONSTR,randX,randY,DANDELIONCHAR,DANDELIONFULLNAME,world);
  }


  if(ptr != nullptr)
    return ptr;
  return nullptr;
}
