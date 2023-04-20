#include "Game.h"
#include "Console.h"
#include "config.h"
#include <ncurses.h>

Game::Game() {
  this->world = nullptr;
  this->nextTurn = false;
  this->continueGame = true;
}

Game::~Game() { delete this->world; }

void Game::startGame() {
  Console *console = Console::getInstance();
  this->continueGame = true;

  if (this->world == nullptr) {
    this->world = new World();
  }

  while (this->continueGame) {

    if (this->nextTurn) {
      this->world->nextTurn();
      this->nextTurn = false;
    }

    this->drawInterface(console);
    this->getPlayerMove();
  }

  return;
}

void Game::menu() {
  Console *console = Console::getInstance();
  char input;
  int cursorPosition = console->getConsoleHeight() / 3 + 2;
  while (true) {
    this->drawMenu(cursorPosition, console);
    // Dont print entered character
    noecho();
    input = getch();
    switch (input) {
    // Arrow up
    case 0x41: {
      if (cursorPosition >= console->getConsoleHeight() / 3 + 2) {
        cursorPosition--;
      }
      break;
    }
    // Arrow down
    case 0x42: {
      if (cursorPosition <= console->getConsoleHeight() / 3 + 3) {
        cursorPosition++;
      }
      break;
    }
    // Enter
    case '\n': {
      switch (cursorPosition - console->getConsoleHeight() / 3) {
      case 1: {
        this->startGame();
        break;
      }
      case 2: {
        this->loadGame();
        break;
      }
      case 3: {
        break;
      }
      case 4: {
        console = nullptr;
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

void Game::loadGame() {}

void Game::saveGame() {}

void Game::getPlayerMove() {
  bool confirmMove = true;
  while (confirmMove) {
    char input = getch();
    char confirm = getch();
    if (confirm == '\n') {
      confirmMove = false;
      this->nextTurn = true;
      switch (input) {
      case 'q': {
        this->continueGame = false;
        break;
      }

      case 's': {

        break;
      }
      case 'p': {

        break;
      }
      // arrow down
      case 0x42: {
        break;
      }
      // arrow left
      case 0x44: {
      }
      // arrow right
      case 0x43: {
        break;
      }
      // arrow up
      case 0x41: {
        break;
      }
      }
    }
  }
}

void Game::drawMenu(int &cursorPosition, Console *console) {
  erase();
  mvprintw(console->getConsoleHeight() - 1, console->getConsoleWidth() - 25,
           "Lukasz Walczak 193530");

  mvprintw(console->getConsoleHeight() / 3, console->getConsoleWidth() / 2 - 10,
           "Menu");

  mvprintw(console->getConsoleHeight() / 3 + 1,
           console->getConsoleWidth() / 2 - 10, "1. New Game");

  mvprintw(console->getConsoleHeight() / 3 + 2,
           console->getConsoleWidth() / 2 - 10, "2. Load Game");

  mvprintw(console->getConsoleHeight() / 3 + 3,
           console->getConsoleWidth() / 2 - 10, "3. Settings TODO");

  mvprintw(console->getConsoleHeight() / 3 + 4,
           console->getConsoleWidth() / 2 - 10, "4. Exit");

  mvprintw(cursorPosition, console->getConsoleWidth() / 2 - 11, "*");
}

void Game::drawLogs(Console *console) {
  // top
  for (int i = console->getConsoleWidth() * 3 / 4;
       i < console->getConsoleWidth() - 4; i++) {
    mvprintw(4, i, "+");
  }

  // bottom
  for (int i = console->getConsoleWidth() * 3 / 4;
       i < console->getConsoleWidth() - 5; i++) {
    mvprintw(console->getConsoleHeight() * 7 / 10, i, "+");
  }

  // left side
  for (int i = console->getConsoleHeight() * 7 / 10; i > 0; i--) {
    mvprintw(i, console->getConsoleWidth() * 3 / 4, "+");
  }

  // right side
  for (int i = console->getConsoleHeight() * 7 / 10; i > 0; i--) {
    mvprintw(i, console->getConsoleWidth() - 5, "+");
  }
}

void Game::drawMapBorders(Console *console) {
  // top
  for (int i = 0; i < MAXDISPLAYWORLDWIDTH; i++)
    mvprintw(0, i, "+");
  // bottom
  for (int i = 0; i < MAXDISPLAYWORLDWIDTH; i++)
    mvprintw(MAXDISPLAYWORLDHEIGHT, i, "+");
  // left
  for (int i = 0; i < MAXDISPLAYWORLDHEIGHT; i++)
    mvprintw(i, 0, "+");
  // right
  for (int i = 0; i < MAXDISPLAYWORLDHEIGHT; i++)
    mvprintw(i, MAXDISPLAYWORLDWIDTH, "+");
}

void Game::drawInterface(Console *console) {
  erase();
  // Drawing Control settings
  mvprintw(console->getConsoleHeight() * 3 / 4,
           console->getConsoleWidth() * 3 / 4, "Controls");

  mvprintw(console->getConsoleHeight() * 3 / 4 + 2,
           console->getConsoleWidth() * 3 / 4, "arrow keys - move");

  mvprintw(console->getConsoleHeight() * 3 / 4 + 4,
           console->getConsoleWidth() * 3 / 4, "enter - confirm turn");

  mvprintw(console->getConsoleHeight() * 3 / 4 + 6,
           console->getConsoleWidth() * 3 / 4, "p - use special ability");

  mvprintw(console->getConsoleHeight() * 3 / 4 + 8,
           console->getConsoleWidth() * 3 / 4, "s -save game");

  mvprintw(console->getConsoleHeight() * 3 / 4 + 10,
           console->getConsoleWidth() * 3 / 4, "q - exit to menu");

  mvprintw(2, console->getConsoleWidth() * 3 / 4 + 8, "Turn: ");

  // Drawing map borders
  this->drawMapBorders(console);
  // Drawing logs
  this->drawLogs(console);
}
