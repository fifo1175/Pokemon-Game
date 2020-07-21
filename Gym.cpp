#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <cctype>
#include <math.h>
#include <cmath>
#include "Pokemon.h"
#include "Gym.h"
using namespace std;


Gym(string TrainerName, vector<Pokemon> TrainerPokemon, int XLoc, int YLoc)
{
    trainerName = TrainerName;
    trainerPokemon = TrainerPokemon;
    xLoc = XLoc;
    yLoc = YLoc;
}
void Gym::setTrainerName(string TrainerName)
{
    trainerName = TrainerName;
}

void Gym::setXLoc(int XLoc)
{
    xLoc = XLoc;
}
void Gym::setYLoc(int YLoc)
{
    yLoc = YLoc;
}
string Gym::getTrainerName()
{
    return trainerName;
}
Pokemon Gym::getPokemon(int idx)
{
    return trainerPokemon[idx];
}
int Gym::getXLoc()
{
    return xLoc;
}
int Gym::getYLoc()
{
    return yLoc;
}

// More complicated member functions

void Gym::gymEncounter()
{
    
}
void Gym::playerWin()
{
    
}
void Gym::trainerWin()
{
    
}
void Gym::setPokemon(vector <Pokemon> TrainerPokemon)
{
    
}