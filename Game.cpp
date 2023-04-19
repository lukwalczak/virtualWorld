#include "Game.h"
#include "config.h"
#include "Console.h"
#include <ncurses.h>

void Game::startGame(){
  

  return;
}

void Game::drawMenu(int &cursorPosition, Console *console){
    erase();
    mvprintw(console->getConsoleHeight()/3, console->getConsoleWidth()/2 - 10, "Menu" );
    mvprintw(console->getConsoleHeight()/3+1, console->getConsoleWidth()/2 - 10, "1. Nowa Gra" );
    mvprintw(console->getConsoleHeight()/3+2, console->getConsoleWidth()/2 - 10, "2. Wczytaj Gre" );
    mvprintw(console->getConsoleHeight()/3+3, console->getConsoleWidth()/2 - 10, "3. Wyjdz" );
    mvprintw(cursorPosition, console->getConsoleWidth()/2 - 11, "*");
}

void Game::menu(){
  Console *console = Console::getInstance();
  char input;
  int cursorPosition = console->getConsoleHeight()/3+2; 
  while(true){
    Game::drawMenu(cursorPosition, console);
    //Dont print entered character
    noecho();
    input = getch();
    switch(input){
      //Arrow up
      case 0x41:{
        if(cursorPosition >= console->getConsoleHeight()/3+2){
          cursorPosition--;
        }
        break;
      }
      //Arrow down
      case 0x42:{
        if(cursorPosition <= console->getConsoleHeight()/3+2){
          cursorPosition++;
        }
        break;
      }
      //Enter
      case '\n':{
        switch(cursorPosition-console->getConsoleHeight()/3){
          case 1:{

            break;
          }
          case 2:{

            break;
          }
          case 3:{
            return;
            break;
          }
        }
      }
      default:
        break;
    }
  }
  return;
}


