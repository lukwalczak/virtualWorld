#pragma once
#include <iostream>
#include "World.h"
#include "Console.h"

class Game final{
private:
  World *world;
  int currentTurn;
  bool nextTurn;
  bool continueGame;
  int worldWidth;
  int worldHeight;
public:
  Game();
  ~Game();
  void startGame();
  void drawInterface(Console &console);
  void drawLogs(Console &console);
  void saveGame();
  void loadGame();
  void menu();
  void drawMenu(int cursorPosition, Console &console);
  void getPlayerMove();
  void drawSettings();
  void drawMapBorders(Console &console);
  void drawEndGame(Console &console);
  void settings();
  void printSettings();
};
