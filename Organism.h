#pragma once
class World;
class Organism {
  protected:
    int strength;
    int initiative;
    int posX;
    int posY;
    int age;
    char organismChar;
    World &world;
  public:
    Organism(World &world);
    const int getStrenght() const;
    const int getInitiative() const;
    const int getPosX() const;
    const int getPosY() const;
    const int getAge() const;
    virtual void collision() = 0;
    virtual void action() = 0;
    virtual void draw() const = 0;
    const World &getWorld();
};
