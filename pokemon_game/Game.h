#include <iostream>
#ifndef GAME_H
#define GAME_H
#include "Tile.h"
#include "Pokemon.h"
#include "Gym.h"
#include "Player.h"

using namespace std;

class Game
{
    public:
    Game(Tile map[][15], int MapRows, int MapCols, vector <Pokemon> WildPokemon, int NumEncounters); // Game constructor  
    int getMapRows(); // getters for map dimensions
    int getMapCols();
    Pokemon findPokemon(string name); // searches for a pokemon in the wildPokemon vector by name
    Pokemon getPokemon(int idx); // searches for a pokemon by index in the vector
    int findPokemonPositionInMapVec(string name);
    void removePokemonFromMapVec(int idx);
    int getNumPokemon(); // get the size of the wildPokemon vector
    void setPokemonInVec(Pokemon name); // Place a pokemon object in the wildPokemon vector
    void placePokemonOnMap(Pokemon objName, int xLoc, int yLoc); // put a pokemon object on the map at x,y
    void quit(); // quit the game
    void readMap(string fileName); // reads the map file and fills in the 2d array with Tile objects
    void printMap(); // prints the whole map
    void printPlayerMap(int xLoc, int yLoc); // prints the player minimap
    void updateScores(string name, int points); // updates the scores at the end of the game
    Tile nearbyCheck(int xLoc, int yLoc); // checks if there are any wildPokemon within 2 squares of the player in any direction
    Tile luckCheck(int xLoc, int yLoc); // checks if there are any pokemon within 3 squares of the player for tryLuck function
    int pokemonEncounter(Pokemon encounteredPokemon, Pokemon current); // player encounters wildPokemon
    void pokemonCenter(); //  player goes to a pokemon center
    void readPokemon(int numToRead, string fileName); // reads the pokemon.txt file and fills in the wildPokemon vector
    int split(string str, char delimeter, string arr[], int len); // to read files
    string changeCase(string name); // can be used to search case insensitive
    Tile getTile(int x, int y); // returns a tile object from x y coordinates
    void setTile(int x, int y, Tile name); // sets a tile object at x y
    void placePlayer(int x, int y); // places the player on the map
    void scatterPokemon(); // scatters 20 random pokemon across the map at the beginning of the game
    Pokemon getRandomPokemon(); // returns a random pokemon from the wildPokemon vector
    int movePlayer(int direction, int x, int y); // moves the player on the map
    Pokemon tryLuck(int x, int y); // the player can try their luck at catching a nearby pokemon
    void PokemonShift(); // moves each pokemon 1 unit in a random direction
    int randomPokemonSpawn(); // end of turn random pokemon spawn chance
    void battle(Pokemon fighters[2]); // a battle between 2 pokemon
    
    
    private:
    Tile map[25][16];
    int mapRows;
    int mapCols;
    vector <Pokemon> wildPokemon; // all wild pokemon
    vector <Pokemon> pokemonOnMap; // all wild pokemon placed on the map
    int numEncounters;
    
};

#endif
