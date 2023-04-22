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
public:
  Game();
  ~Game();
  void startGame();
  void drawInterface(Console *console);
  void drawLogs(Console *console);
  void saveGame();
  void loadGame();
  void menu();
  void drawMenu(int &cursorPosition, Console *console);
  void getPlayerMove();
  void drawSettings();
  void drawMapBorders(Console *console);
  void endGame(Console *console);
  void settings();
};
