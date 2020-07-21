#include <iostream>
#ifndef TILE_H
#define TILE_H
#include "Pokemon.h"

using namespace std;

class Tile
{
    public:
    Tile(char Type, bool HasGym, bool HasCenter, bool HasPokemon, int XLoc, int YLoc, Pokemon BoiPostedUp[], Pokemon TrainerPokemon[]);
    Tile(); // constructors
    void makeType(char Type); // sets the type of the tile
    void setGym(bool HasGym); // sets if the tile has a gym
    void setCenter(bool HasCenter); // sets if the tile has a pokemon center
    void setPokemonTile(bool HasPokemon); // ets if the tile has a pokemon
    void placePokemonOnTile(Pokemon objName); // places a pokemon on that tile
    void giveTrainerPokemon(Pokemon pokObject, int arrayPos); // gives a trainer(gym) a pokemon
    char getType(); // get the type of tile
    bool checkGym(); // check if there is a gym
    bool checkCenter(); // check if there is a center
    bool checkPokemon(); // check if there is a pokemon
    void setXLoc(int XLoc); // sets the x position of the tile
    void setYLoc(int YLoc); // sets the y position of the tile
    Pokemon getTilePokemon(); // returns the pokemon object that the tile holds
    void removePokemonFromTile(); // removes the pokemon object from the array of that tile
    
    
    
    private:
    char type;
    bool hasGym;
    bool hasCenter;
    bool hasPokemon;
    Pokemon tilePokemon[1];
    Pokemon trainerPokemon[6];
    int xLoc;
    int yLoc;
    

    
};

#endif