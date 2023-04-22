#pragma once
#include <string>
class World;
class Organism {
  protected:
    int strength;
    int initiative;
    int posX;
    int posY;
    int age;
    char organismChar;
    std::string fullOrganismName;
    World &world;
  public:
    Organism(int strength, int initiative, int posX, int posY, char organismChar, std::string fullOrganismName, World &world);
    virtual ~Organism();
    const int getStrenght() const;
    const int getInitiative() const;
    const int getPosX() const;
    const int getPosY() const;
    const int getAge() const;
    const std::string getFullOrganismName() const;
    const char getOrganismChar() const;
    virtual bool collision(Organism *colidingOrganism) = 0;
    virtual void action() = 0;
    void draw() const;
    const World &getWorld();
    virtual bool checkMove(int dx, int dy);
    virtual void kill();
};
