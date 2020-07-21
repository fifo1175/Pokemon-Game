#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <cctype>
#include <math.h>
#include <cmath>
#include "Pokemon.h"
using namespace std;

Pokemon::Pokemon(string Name, string Type, int hp, int Attack, int Defense, int Speed, int Max, int XLoc, int YLoc, bool IsWild)
{
    name = Name;
    type = Type;
    HP = hp;
    attack = Attack;
    defense = Defense;
    speed = Speed;
    xLoc = XLoc;
    yLoc = YLoc;
    max = Max;
    isWild = IsWild;
}

Pokemon::Pokemon()
{
    name = "";
    type = "";
    HP = 0;
    attack = 0;
    defense = 0;
    speed = 0;
    xLoc = 0;
    yLoc = 0;
    max = 0;
    isWild = true;
    
}
string Pokemon::getName()
{
    return name;
}
    
    
void Pokemon::setName(string Name)
{
    name = Name;
}
    
    
string Pokemon::getType()
{
    return type;
}
    
    
void Pokemon::setType(string Type)
{
    type = Type;
}
    
int Pokemon::getHP()
{
    return HP;
}
    
    
void Pokemon::setHP(int hp)
{
    HP = hp;
}
    
    
int Pokemon::getAttack()
{
    return attack;
}
    
    
void Pokemon::setAttack(int Attack)
{
    attack = Attack;
}
    
    
int Pokemon::getDefense()
{
    return defense;
}
    
    
void Pokemon::setDefense(int Defense)
{
    defense = Defense;
}
    
    
int Pokemon::getSpeed()
{
    return speed;
}
    
    
void Pokemon::setSpeed(int Speed)
{
    speed = Speed;
}
    
    
int Pokemon::getX()
{
    return xLoc;
}
    
    
int Pokemon::getY()
{
    return yLoc;
}
    
    
void Pokemon::setX(int XLoc)
{
    xLoc = XLoc;
}
    
    
void Pokemon::setY(int YLoc)
{
    yLoc = YLoc;
}
    
    
int Pokemon::getMax()
{
    return max;
}
    
    
void Pokemon::setMax(int Max)
{
    max = Max;
}

void Pokemon::setIndex(int Idx)
{
    idx = Idx;
}
    
int Pokemon::getIndex()
{
    return idx;
}
    
    
bool Pokemon::checkWild()
{
    return isWild;
}


// More complicated member functions

void Pokemon::displayPokemonStats()
{
    cout << "Name: " << name << ", HP: " << HP << ", A: " << attack << ", D: " << defense << ", S: " << speed << ", M: " << max << endl;
    
}

void Pokemon::flee()
{
    
}
void Pokemon::heal()
{
    
}
void Pokemon::faint()
{
    
}
void Pokemon::levelUp()
{
    HP = HP + (HP * 0.02);
    if(attack + (attack * 0.02) <= max)
    {
        attack = attack + (attack * 0.02);
    }
    if(defense + (defense * 0.02) <= max)
    {
        defense = defense + (defense * 0.02);
    }
    speed = speed + (speed * 0.02);
    
}