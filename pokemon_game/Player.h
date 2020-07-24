#include <iostream>
#ifndef PLAYER_H
#define PLAYER_H
#include "Pokemon.h"
using namespace std;

class Player
{
    public:
    Player(string Name, Pokemon CurrentPokemon[1], vector <Pokemon> ActivePokemon, vector <Pokemon> pokedex, int XLoc, int YLoc, int Pokeballs, int Points, int Badges);
    Player();
    void rest(); // when the player chooses to rest for their turn
    void fight();
    void run();
    void switchPokemon();
    void addPokemonActive(Pokemon objName); // adds a pokemon to the players active party
    void addPokemonPokedex(Pokemon objName); // adds a pokemon to the players pokedex
    string getName(); // get the players name
    void setPlayerName(string name); // set the player's name
    void setPokeballs(int Pokeballs);
    void setPoints(int Points); // update their points
    void setBadges(int Badges); // update their badges
    void setXLoc(int x); // get and set the player's coordinates
    void setYLoc(int y);
    int getXLoc();
    int getYLoc();
    void updateLocation(int direction); // when the player moves in a direction, update their location
    int getPokeballs();
    int getPoints();
    int getBadges();
    int getNumActivePokemon(); // returns the number of active pokemon
    int getNumPokedexPokemon(); // returns the number of pokemon in the pokedex
    Pokemon getActivePokemon(int idx); // returns a pokemon at an index in the active pokemon vector
    Pokemon getCurrentPokemon(); // returns the current pokemon that the player is using
    
    private:
    string name;
    vector <Pokemon> activePokemon; // up to 6 active pokemon
    vector <Pokemon> Pokedex; // the rest of the player's pokemon goes in their pokedex
    Pokemon currentPokemon[1]; // the pokemon that the player is currently using
    int xLoc;
    int yLoc;
    int pokeballs;
    int points;
    int badges;
    
};

#endif
