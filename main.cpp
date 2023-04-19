#include "Game.h"
#include <ncurses.h>

int main(){
  initscr();
  Game game;
  game.menu();
  endwin();
  return 0;
}
