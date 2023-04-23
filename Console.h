#pragma once
#include <iostream>
#include <ncurses.h>

class Console{
private:
  int maxX;
  int maxY;
public:
  Console();
  const int &getConsoleWidth() const;
  const int &getConsoleHeight() const;
};
