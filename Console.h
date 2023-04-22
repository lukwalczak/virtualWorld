#pragma once
#include <iostream>
#include <ncurses.h>

class Console{
private:
  Console();
  static std::mutex mutex;
  static Console *pConsole;
  int maxX;
  int maxY;
public:
  Console(Console &other);
  ~Console();
  void operator=(const Console &);
  static Console *getInstance();
  const int &getConsoleWidth() const;
  const int &getConsoleHeight() const;
};
