#include "Game.h"
#include "Console.h"
#include "config.h"
#include <ncurses.h>
#include <stdexcept>

Game::Game() {
  this->continueGame = true;
  this->currentTurn = 1;
  this->worldWidth = WORLDWIDTH;
  this->worldHeight = WORLDHEIGHT;
  this->world = new World(this->currentTurn, this->worldWidth, this->worldHeight);
}

Game::~Game() { delete this->world; }

void Game::startGame() {
  delete this->world;
  this->world = new World(this->currentTurn, this->worldWidth, this->worldHeight);
  this->currentTurn = 1;
  Console console;
  this->continueGame = true;

  world->generateNewWorld();

  while (this->continueGame && this->world->isHumanAlive()) {
    this->world->startTurn();
    this->drawInterface(console);
    this->world->draw();
    this->world->firstActionTurn();
    if(this->world->isHumanAlive())
      this->getPlayerMove();
    this->world->turn();
    this->world->endTurn();
    this->currentTurn++;
  }

  if(!this->world->isHumanAlive()){
    this->drawEndGame(console);
    getch();
  }

  return;
}

void Game::menu() {
  Console console; 
  char input;
  int cursorPosition = console.getConsoleHeight() / 3 + 2;
  while (true) {
    this->drawMenu(cursorPosition, console);
    // Dont print entered character
    noecho();
    input = getch();
    switch (input) {
    // Arrow up
    case 0x41: {
      if (cursorPosition >= console.getConsoleHeight() / 3 + 2) {
        cursorPosition--;
      }
      break;
    }
    // Arrow down
    case 0x42: {
      if (cursorPosition <= console.getConsoleHeight() / 3 + 3) {
        cursorPosition++;
      }
      break;
    }
    // Enter
    case '\n': {
      switch (cursorPosition - console.getConsoleHeight() / 3) {
      case 1: {
        this->startGame();
        break;
      }
      case 2: {
        this->loadGame();
        break;
      }
      case 3: {
        this->settings();
        break;
      }
      case 4: {
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

void Game::settings(){
  erase();
  Console console;
  mvprintw(console.getConsoleHeight()/2, console.getConsoleWidth()/2, "Enter world width: ");
  std::string height, width;
  echo();
  int ch = getch();
  while( ch != '\n'){
    width.push_back(ch);
    ch = getch();
  }
  erase();
  mvprintw(console.getConsoleHeight()/2, console.getConsoleWidth()/2, "Enter world height: ");
  ch = getch();
  while(ch != '\n'){
    height.push_back(ch);
    ch = getch();
  }
  int worldWidth, worldHeight;
  try{
    worldWidth = std::stoi(width);
    worldHeight = std::stoi(height);
    this->worldWidth = worldWidth;
    this->worldHeight = worldHeight;
  } catch(std::invalid_argument &e){

  } catch(std::out_of_range &e){

  }
  noecho();
  return;
}

void Game::printSettings(){
}

void Game::getPlayerMove() {
  bool confirmMove = true;
  while (confirmMove) {
    char input = getch();
    char confirm = getch();
    if (confirm == '\n') {
      switch (input) {
      case 'q': {
        this->continueGame = false;
        confirmMove = false;
        break;
      }

      case 's': {

        break;
      }
      case 'p': {
        if(this->world->getHuman()->useAbility()){
          confirmMove = false;
        }
        break;
      }
      // arrow down
      case 0x42: {
        if(this->world->getHuman()->action(1, 0)){
          confirmMove = false;
          }
          break;
      }
      // arrow left
      case 0x44: {
        if(this->world->getHuman()->action(0, -1)){
        confirmMove = false;
        }
        break;
      }
      // arrow right
      case 0x43: {
        if(this->world->getHuman()->action(0, 1)){
        confirmMove = false;
        }
        break;
      }
      // arrow up
      case 0x41: {
        if(this->world->getHuman()->action(-1, 0)){
        confirmMove = false;
        }
        break;
      }
      }
    }
  }
}

void Game::drawMenu(int cursorPosition, Console &console) {
  erase();
  mvprintw(console.getConsoleHeight() - 1, console.getConsoleWidth() - 25,
           "Lukasz Walczak 193530");

  mvprintw(console.getConsoleHeight() / 3, console.getConsoleWidth() / 2 - 10,
           "Menu");

  mvprintw(console.getConsoleHeight() / 3 + 1,
           console.getConsoleWidth() / 2 - 10, "1. New Game");

  mvprintw(console.getConsoleHeight() / 3 + 2,
           console.getConsoleWidth() / 2 - 10, "2. Load Game");

  mvprintw(console.getConsoleHeight() / 3 + 3,
           console.getConsoleWidth() / 2 - 10, "3. Settings");

  mvprintw(console.getConsoleHeight() / 3 + 4,
           console.getConsoleWidth() / 2 - 10, "4. Exit");

  mvprintw(cursorPosition, console.getConsoleWidth() / 2 - 11, "*");
}

void Game::drawLogs(Console &console) {
  // top
  for (int i = console.getConsoleWidth() * 3 / 4;
       i < console.getConsoleWidth() - 4; i++) {
    mvprintw(4, i, "+");
  }

  // bottom
  for (int i = console.getConsoleWidth() * 3 / 4;
       i < console.getConsoleWidth() - 5; i++) {
    mvprintw(console.getConsoleHeight() * 7 / 10, i, "+");
  }

  // left side
  for (int i = console.getConsoleHeight() * 7 / 10; i > 0; i--) {
    mvprintw(i, console.getConsoleWidth() * 3 / 4, "+");
  }

  // right side
  for (int i = console.getConsoleHeight() * 7 / 10; i > 0; i--) {
    mvprintw(i, console.getConsoleWidth() - 5, "+");
  }

  //drawing logs
  std::vector<std::string> logs = this->world->getLastLogs();
  for(int i = logs.size(); i > 0; i--){
    mvprintw(4 + i , console.getConsoleWidth() * 3 / 4 + 2, logs[i].c_str());
  }
}

void Game::drawMapBorders(Console &console) {
  // top
  for (int i = 0; i < this->worldWidth + 2; i++)
    mvprintw(0, i, "+");
  // bottom
  for (int i = 0; i < this->worldWidth + 2; i++)
    mvprintw(this->worldHeight + 1, i, "+");
  // left
  for (int i = 0; i < this->worldHeight + 2; i++)
    mvprintw(i, 0, "+");
  // right
  for (int i = 0; i < this->worldHeight + 2; i++)
    mvprintw(i, this->worldWidth + 1, "+");
}

void Game::drawInterface(Console &console) {
  erase();
  // Drawing Control settings
  mvprintw(console.getConsoleHeight() * 3 / 4,
           console.getConsoleWidth() * 3 / 4, "Controls");

  mvprintw(console.getConsoleHeight() * 3 / 4 + 2,
           console.getConsoleWidth() * 3 / 4, "arrow keys - move");

  mvprintw(console.getConsoleHeight() * 3 / 4 + 4,
           console.getConsoleWidth() * 3 / 4, "enter - confirm turn");

  mvprintw(console.getConsoleHeight() * 3 / 4 + 6,
           console.getConsoleWidth() * 3 / 4, "p - use special ability");

  mvprintw(console.getConsoleHeight() * 3 / 4 + 8,
           console.getConsoleWidth() * 3 / 4, "s -save game // not implemented");

  mvprintw(console.getConsoleHeight() * 3 / 4 + 10,
           console.getConsoleWidth() * 3 / 4, "q - exit to menu");
  char turnText[15];
  sprintf(turnText, "Turn: %d", this->currentTurn);
  mvprintw(2, console.getConsoleWidth() * 3 / 4 + 8, turnText);

  // Drawing map borders
  this->drawMapBorders(console);
  // Drawing logs
  this->drawLogs(console);
}

void Game::drawEndGame(Console &console){
  erase();
  mvprintw(console.getConsoleHeight()/2, console.getConsoleWidth()/2, "Game ended, you died");
}
