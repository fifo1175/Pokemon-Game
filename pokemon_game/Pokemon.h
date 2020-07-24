#include <iostream>
#ifndef POKEMON_H
#define POKEMON_H

using namespace std;

class Pokemon
{
    public:
    Pokemon(string Name, string Type, int hp, int Attack, int Defense, int Speed, int Xloc, int YLoc, int Max, bool IsWild);
    Pokemon();
    string getName();
    void setName(string Name);
    string getType();
    void setType(string Type);
    int getHP();
    void setHP(int hp);
    int getAttack();
    void setAttack(int Attack);
    int getDefense();
    void setDefense(int Defense);
    int getSpeed();
    void setSpeed(int Speed);
    int getX();
    int getY();
    void setX(int XLoc);
    void setY(int YLoc);
    int getMax();
    void setMax(int Max);
    int getIndex();
    void setIndex(int Idx);
    bool checkWild();
    void displayPokemonStats();
    
    void flee();
    void heal();
    void faint();
    void levelUp();
    
    
    
    
    private:
    string name;
    string type;
    int HP;
    int attack;
    int defense;
    int speed;
    int xLoc;
    int yLoc;
    int max;
    bool isWild;
    int idx;
    
    
};

#endif
