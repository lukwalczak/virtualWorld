#pragma once

class Organism {
  protected:
    int strength;
    int initiative;
    int posX;
    int posY;
    char organismChar;
  public:
    const int getStrenght() const;
    const int getInitiative() const;
    const int getPosX() const;
    const int getPosY() const;
    virtual void collision() = 0;
    virtual void action() = 0;
    virtual void draw() const = 0;
};
