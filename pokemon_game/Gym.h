#include <iostream>
#ifndef GYM_H
#define GYM_H
#include <string>
#include "Pokemon.h"

using namespace std;

class Gym
{
    public:
    Gym(string TrainerName, vector <Pokemon> TrainerPokemon, int XLoc, int YLoc);
    void setTrainerName(string TrainerName);
    void setPokemon(vector <Pokemon> TrainerPokemon);
    void setXLoc(int XLoc);
    void setYLoc(int YLoc);
    string getTrainerName();
    Pokemon getPokemon(int idx);
    int getXLoc();
    int getYLoc();
    void gymEncounter();
    void playerWin();
    void trainerWin();
    
    
    private:
    string trainerName;
    vector <Pokemon> trainerPokemon;
    int xLoc;
    int yLoc;
    
    
    
};

#endif
