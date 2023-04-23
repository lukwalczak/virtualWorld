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
  void clearWorld();
  int &gameTurn;
public:
  World(int &gameTurn, int worldWidth, int worldHeight);
  ~World();
  void firstActionTurn();
  void turn();
  void sortOrganisms();
  void draw();
  Human *getHuman();
  int getWidth();
  int getHeight();
  bool isHumanAlive() const;
  void generateNewWorld();
  Organism *getOrganismAtXY(int x, int y);
  void removeOrganism(Organism *organism);
  void addLog(std::string log);
  static bool compareOrganisms(Organism *o1, Organism *o2);
  std::vector<std::string> getLogs();
  std::vector<std::string> getLastLogs();
  void addOrganism(Organism *organism);
  void startTurn();
  void endTurn();
};
