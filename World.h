#pragma once
#include "Organism.h"
#include <vector>
#include <string>
#include "Human.h"
class Organism;
class World {
private:
  std::vector<Organism*> organisms;
  std::vector<std::string> logs;
  Human *human;
  int width;
  int height;
  void generateAnimals();
public:
  World();
  ~World();
  void firstActionTurn();
  void turn();
  void sortOrganisms();
  void draw();
  Human *getHuman();
  bool isHumanAlive() const;
  void generateNewWorld();
  Organism *getOrganismAtXY(int x, int y);
  void removeOrganism(Organism *organism);
  void addLog(std::string log);
  std::vector<std::string> getLogs();
  std::vector<std::string> getLastLogs();
};
