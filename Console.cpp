#include "Console.h"
#include <ncurses.h>

Console::Console(){
  this->maxX = 0;
  this->maxY = 0;
  getmaxyx(stdscr, this->maxY, this->maxX);
}

const int &Console::getConsoleHeight() const { return this->maxY; }

const int &Console::getConsoleWidth() const { return this->maxX; }
