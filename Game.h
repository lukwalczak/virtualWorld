#pragma once
#include <iostream>
#include "World.h"
#include "Console.h"

class Game{
private:

public:
  void startGame();
  void drawInterface();
  void saveGame();
  void loadGame();
  void menu();
  void drawMenu(int &cursorPosition, Console *console);
};
