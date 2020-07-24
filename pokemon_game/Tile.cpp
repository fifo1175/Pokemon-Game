#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <cctype>
#include <math.h>
#include <cmath>
#include "Tile.h"
#include "Pokemon.h"
using namespace std;

Tile::Tile(char Type, bool HasGym, bool HasCenter, bool HasPokemon, int XLoc, int YLoc, Pokemon BoiPostedUp[], Pokemon TrainerPokemon[])
{
    type = Type;
    hasGym = HasGym;
    hasCenter = HasCenter;
    hasPokemon = HasPokemon; // parameterized constructor
    xLoc = XLoc;
    yLoc = YLoc;
    tilePokemon[1];
    trainerPokemon[6];
}
Tile::Tile() // default constructor
{
    hasGym = false;
    hasCenter = false;
    hasPokemon = false;
    xLoc = 0;
    yLoc = 0;
    tilePokemon[1];
    trainerPokemon[6];
}

void Tile::placePokemonOnTile(Pokemon objName) // places a pokemon object in the tile's array
{
    tilePokemon[0] = objName;
}

Pokemon Tile::getTilePokemon() // returns the pokemon object in the tile's array
{
    return tilePokemon[0];
}

void Tile::makeType(char Type) // sets the type
{
    type = Type;
}

void Tile::setGym(bool HasGym) // sets if the tile has a gym
{
    hasGym = HasGym;
}

void Tile::setCenter(bool HasCenter) // sets if the tile has a center
{
    hasCenter = HasCenter;
}

void Tile::setPokemonTile(bool HasPokemon) // sets if the tile has a pokemon
{
    hasPokemon = HasPokemon;
}

void Tile::giveTrainerPokemon(Pokemon pokObject, int arrayPos) // gives the trainer on that tile a pokemon in their array
{
    trainerPokemon[arrayPos] = pokObject;
}

char Tile::getType() // returns the type of tile
{
    return type;
}

bool Tile::checkGym() // returns if there is a gym
{
    return hasGym;
}

bool Tile::checkCenter() // returns if there is a center
{
    return hasCenter;
}

bool Tile::checkPokemon() // returns if there is a pokemon
{
    return hasPokemon;
}

void Tile::setXLoc(int XLoc) // sets the x coordinate
{
    xLoc = XLoc;
}

void Tile::setYLoc(int YLoc) // sets the y coordinate
{
    yLoc = YLoc;
}

void Tile::removePokemonFromTile() // removes the pokemon from that tile's array
{
    tilePokemon[0] = {};
}
