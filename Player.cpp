#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <cctype>
#include <math.h>
#include <cmath>
#include "Pokemon.h"
#include "Player.h"
using namespace std;

Player::Player(string Name, Pokemon CurrentPokemon[1], vector <Pokemon> ActivePokemon, vector <Pokemon> pokedex, int XLoc, int YLoc, int Pokeballs, int Points, int Badges)
{
    name = Name;
    activePokemon = ActivePokemon;
    Pokedex = pokedex;
    currentPokemon[1] = CurrentPokemon[1];    // paramaterized constructor
    xLoc = XLoc;
    yLoc = YLoc;
    pokeballs = Pokeballs;
    points = Points;
    badges = Badges;
}
Player::Player() // default constructor
{
    name = "";
    currentPokemon[1];
    activePokemon = {};
    Pokedex = {};
    xLoc = 0;
    yLoc = 0;
    pokeballs = 10;
    points = 0;
    badges = 0;
}
string Player::getName()         // getters and setters for the player's private data members
{
    return name;
}
void Player::setPlayerName(string Name)
{
    name = Name;
}
void Player::setPokeballs(int Pokeballs)
{
    pokeballs = Pokeballs;
}
void Player::setPoints(int Points)
{
    points = Points;
}
void Player::setBadges(int Badges)
{
    badges = Badges;
}
void Player::setXLoc(int x)
{
    xLoc = x;
}
void Player::setYLoc(int y)
{
    yLoc = y;
}
int Player::getXLoc()
{
    return xLoc;
}
int Player::getYLoc()
{
    return yLoc;
}
int Player::getPokeballs()
{
    return pokeballs;
}
int Player::getPoints()
{
    return points;
}
int Player::getBadges()
{
    return badges;
}

// More complicated member functions

void Player::addPokemonActive(Pokemon objName) // adds a pokemon to the players active party
{
    activePokemon.push_back(objName);
    
    if(activePokemon.size() == 1) // if it is their only pokemon, make it their current pokemon to be used
    {
        currentPokemon[0] = objName;
    }
    
}

void Player::addPokemonPokedex(Pokemon objName)
{
    Pokedex.push_back(objName);
}

void Player::updateLocation(int direction) // Updates player's x and y coordinates when they move
{
    if(direction == 1) // the player moved north
    {
        xLoc = xLoc - 1;
    }
    if(direction == 2) // the player moved east
    {
        yLoc = yLoc + 1;
    }
    if(direction == 3) // the player moved south
    {
        xLoc = xLoc + 1;
    }
    if(direction == 4) // the player moved west
    {
        yLoc = yLoc - 1;
    }
}

void Player::rest() // rest for the player's turn
{
    for(int i = 0; i < activePokemon.size(); i++)
    {
        int currentHP = activePokemon.at(i).getHP(); // increaese each pokemon in the active party's HP
        int newHP = currentHP + 1;
        activePokemon.at(i).setHP(newHP);
    }
    
    pokeballs = pokeballs - 1; // reduce pokeballs by 1
}

void Player::fight()
{
    
}
void Player::run()
{
    
}
void Player::switchPokemon()
{
    cout << "Pick another active Pokemon" << endl;
    for(int i = 0; i < activePokemon.size(); i++)
    {
        cout << i + 1 << ". " << activePokemon.at(i).getName() << endl;
    }
    string choice;
    getline(cin, choice);
    int option = stoi(choice);
    while(option < 1 || option > activePokemon.size())
    {
        cout << "Invalid option.  Please choose again." << endl;
        string choice;
        getline(cin, choice);
        option = stoi(choice);
    }
    currentPokemon[0] = activePokemon.at(option - 1);
    
    
}
int Player::getNumActivePokemon() // return the size of the active pokemon vector
{
    return activePokemon.size();
}
int Player::getNumPokedexPokemon() // return the size of the pokedex vector
{
    return Pokedex.size();
}
Pokemon Player::getCurrentPokemon() // returns the current pokemon that the player is using
{
    return currentPokemon[0];
}

Pokemon Player::getActivePokemon(int idx) // returns an active pokemon at an index in the vector
{
    return activePokemon.at(idx);
}