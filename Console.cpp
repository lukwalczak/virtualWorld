#include "Console.h"
#include <ncurses.h>

Console *Console::pConsole{nullptr};
std::mutex Console::mutex;

Console::Console(){
  this->maxX = 0;
  this->maxY = 0;
  getmaxyx(stdscr, this->maxY, this->maxX);
}

Console::~Console(){
  delete this;
}

int Console::getConsoleHeight(){ return this->maxY; }

int Console::getConsoleWidth(){ return this->maxX; }

Console *Console::getInstance(){
  std::lock_guard<std::mutex> lock(mutex);
  if(pConsole == nullptr){
    pConsole = new Console();
  }
  return pConsole;
}