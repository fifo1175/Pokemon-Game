#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <cctype>
#include <math.h>
#include <cmath>
#include "Game.h"
#include "Pokemon.h"
#include "Tile.h"
#include <ctime>
using namespace std;

Game::Game(Tile Map[][15], int MapRows, int MapCols, vector <Pokemon> WildPokemon, int NumEncounters) // game constructor
{
    Pokemon singleArray[1]; // empty arrays to make the empty Tile object with
    Pokemon trainerArray[6];
    Tile emptyTile('e', false, false, false, 0, 0, singleArray, trainerArray);
    for(int i = 0; i < 25; i++)
    {
        for(int j = 0; i < 16; i++)
        {
            map[i][j] = emptyTile; // initializes the 2d map array with empty Tile objects
        }
    }
    mapRows = MapRows;
    mapCols = MapCols;
    wildPokemon = WildPokemon; 
    numEncounters = NumEncounters;
}

int Game::getMapRows()
{
    return mapRows;
}

int Game::getMapCols()
{
    return mapCols;
}

int Game::split(string str, char delimeter, string arr[], int len) // old split function to read files with
{
    string tempString;
    int i = 1;
    int numSplits = 1;

    if(str == "")
    {
        return 0;
    }
    else
    {
        for(i = 0; i < str.length(); i++)
        {
            if(str[i] != delimeter)
            {
                tempString = tempString + str[i];
            }
            else
            {
                if(i != 0 && i != str.length() - 1 && tempString.length() != 0)
                {
                    arr[numSplits - 1] = tempString;
                    numSplits += 1;
                    tempString = "";
                }
            }
        }
        arr[numSplits - 1] = tempString;
    }
    if(numSplits > len)
    {
        return -1;
    }
    return numSplits;
}

string Game::changeCase(string name) // function that changes a string to all lowercase letters
{
    string myName;
    int characterInt;
    char newChar;
    
    for(int i = 0; i < name.length(); i++)
    {
        if(name[i] >= 'A' && name[i] <= 'Z') // checks if a character is an uppercase letter
        {
            characterInt = name[i];
            characterInt = characterInt + 32; // changes ascii value to lowercase ascii value
            newChar = characterInt;
            name[i] = newChar; 
            
        }
        
    }
    
    myName = name; // the new myName string is now username, which is composed of all lowercase letters
    
    return myName;
}

void Game::readPokemon(int numToRead, string fileName) // read the pokemon from pokemon.txt and fill up the wildPokemon vector
{
    ifstream myFile;
    
    myFile.open(fileName);
    
    if(myFile.is_open())
    {
        string arr[9] = {}; // split function array
        string name;
        string type;
        int hp;
        int attack;
        int defense;
        int speed;
        int max;
        string line = "";
        
        int count = 0;
        
        while(getline(myFile, line) && count <= numToRead) // numToRead can be set to however many Pokemon you want there to be in the game
        {
            if(line != "")
            {
                split(line, ',', arr, 8);
                if(count > 0) // this ignores the first line in the file because it is not a pokemon
                {
                    name = arr[1];            // sets all the stat variables to what's in the array from split()
                    hp = stoi(arr[2]);
                    attack = stoi(arr[3]);
                    defense = stoi(arr[4]);
                    speed = stoi(arr[5]);
                    max = stoi(arr[6]);
                    type = arr[7];
                    Pokemon newPokemon(name, type, hp, attack, defense, speed, max, 0, 0, true); // create a new Pokemon object with the stats from the variables above
                    wildPokemon.push_back(newPokemon);  // place the new Pokemon object in the vector
                }
                count++;
            }
            
        }
    }
}

Pokemon Game::findPokemon(string name) // searches for a pokemon by name
{
    string newName = changeCase(name); // case insensitive search
    string searchName;
    bool pokemonFound = false;
    int position;
    for(int i = 0; i < wildPokemon.size(); i++) // goes through the wildPokemon vector
    {
        searchName = wildPokemon.at(i).getName(); 
        searchName = changeCase(searchName); // gets the name of each pokemon, and changes it to all lowercase
        
        if(searchName == newName)
        {
            pokemonFound = true;
            position = i; // record the position in the vector where the pokemon was found
            
        }
    }
    
    if(pokemonFound == false)
    {
        cout << name << " was not found." << endl;
        return Pokemon(); // can't return nullptr? returning empty pokemon object instead
    }
    
    if(pokemonFound == true)
    {
        Pokemon newObject = wildPokemon.at(position); // new pokemon object is assigned to the pokemon at the position where the name was found
        wildPokemon.erase(wildPokemon.begin() + position); // removes the pokemon from the vector
        return newObject;
    }

    return Pokemon();
}

int Game::findPokemonPositionInMapVec(string name)
{
    string newName = changeCase(name); // case insensitive search
    string searchName;
    bool pokemonFound = false;
    int position;
    for(int i = 0; i < pokemonOnMap.size(); i++) // goes through the wildPokemon vector
    {
        searchName = pokemonOnMap.at(i).getName(); 
        searchName = changeCase(searchName); // gets the name of each pokemon, and changes it to all lowercase
        
        if(searchName == newName)
        {
            pokemonFound = true;
            position = i; // record the position in the vector where the pokemon was found
            return position;
            
        }
    }
    
    return 0;
}
void Game::setPokemonInVec(Pokemon name) // puts a pokemon object in the wildPokemon vector
{
    wildPokemon.push_back(name);
}

int Game::getNumPokemon() // getter for the vector size
{
    return wildPokemon.size();
}

Pokemon Game::getPokemon(int idx) // returns a pokemon at an index
{
    return wildPokemon.at(idx);
}

void Game::placePokemonOnMap(Pokemon objName, int x, int y) // places a pokemon on the map at x y
{
    map[x][y].setPokemonTile(true); // the tile will now show that there is a pokemon there when checked
}

Pokemon Game::getRandomPokemon()
{
    srand(time(NULL));

    int x = rand() % 150 + 0; // generates a random number between 0 and 150
        
    Pokemon randomPokemon = wildPokemon.at(x); // pokemon object is equal to a pokemon in the vector at position x
    
    return randomPokemon;
}

void Game::scatterPokemon()
{
    srand(time(NULL));
    
    int numPlaced = 0; // this keeps track of how many pokemon have actually been placed, in case the random tile generated cannot have a pokemon there
    
    while(numPlaced < 20)
    {
        int p = rand() % 150 + 0; // random pokemon
    
        int x = rand() % 24 + 0; // random x coordinate (row)
        
        int y = rand() % 15 + 0; // random y coordinate (column)
        
        
        Pokemon randomBoi = wildPokemon.at(p); // random pokemon object from the vector
        
        if(map[x][y].getType() != 'C' && map[x][y].getType() != 'G' && map[x][y].getType() != '@' && map[x][y].getType() != '~' && map[x][y].checkPokemon() != true) // checking if the tile can house a pokemon
        {
            randomBoi.setX(x);
            randomBoi.setY(y);
            map[x][y].setPokemonTile(true);
            map[x][y].placePokemonOnTile(randomBoi);
            pokemonOnMap.push_back(randomBoi);
            
            numPlaced++;
        }
    }
    
    
}

void Game::quit()
{
    
}

Tile Game::getTile(int x, int y)
{
    return map[x][y]; // return a tile at x, y coordinates
}

void Game::setTile(int x, int y, Tile name) // set a tile at x y coordinates
{
    map[x][y] = name;
}

void Game::readMap(string fileName) // read the map from map.txt
{
    srand(time(NULL));
    
    ifstream myFile;
    
    myFile.open(fileName);
    
    if(myFile.is_open())
    {
        string arr[16] = {}; // the array to be used in the split function
        string line = "";
        string current;
        int j = 0; // the counter for the while loop
        
        while(getline(myFile, line) && j < 25) // while loop reads each line (row) of the map
        {
            split(line, ',', arr, 16); // splits each row into 16 strings
            for(int i = 0; i < 16; i++) // iterates across the row
            {
                Tile newTile; // creates a new tile for each string in the row
                current = arr[i];
                if(current == "w")
                {
                    newTile.makeType('~'); // water tile
                    newTile.setGym(false);
                    newTile.setCenter(false);
                    newTile.setPokemonTile(false);
                    newTile.setXLoc(i); // the new tile's location must be set
                    newTile.setYLoc(j);
                }
                if(current == "p")
                {
                    newTile.makeType('*'); // land tile
                    newTile.setGym(false);
                    newTile.setCenter(false);
                    newTile.setPokemonTile(false);
                    newTile.setXLoc(i);
                    newTile.setYLoc(j);
                }
                if(current == "G")
                {
                    newTile.makeType('G'); // gym tile
                    newTile.setGym(true);
                    newTile.setCenter(false);
                    newTile.setPokemonTile(false);
                    newTile.setXLoc(i);
                    newTile.setYLoc(j);
    
                    int times = rand() % 6 + 1; // gives the trainer at the gym between 1 and 6 pokemon
                    
                    for(int i = 0; i < times; i++)
                    {
                        int x = rand() % 150 + 0;
        
                        Pokemon newPokemon = wildPokemon.at(x); // random pokemon generated
                        
                        newTile.giveTrainerPokemon(newPokemon, i); // the trainerPokemon array is updated
                    }
                
                }
                if(current == "C")
                {
                    newTile.makeType('C'); // pokemon center tile
                    newTile.setGym(false);
                    newTile.setCenter(true);
                    newTile.setPokemonTile(false);
                    newTile.setXLoc(i);
                    newTile.setYLoc(j);
                }
                
                map[j][i] = newTile; // places the newTile object in the 2d map array
                
            }
            
            j++;
        }
    }
    
    myFile.close();
}

void Game::printMap() // prints entire map
{
    for(int i = 0; i < 25; i++)
    {
        for(int j = 0; j < 16; j++)
        {
            cout << map[i][j].getType() << " ";
        }
        
        cout << endl; // goes to next row
    }
}
void Game::placePlayer(int x, int y) // puts player on the map
{
    map[x][y].makeType('@');
}

void Game::printPlayerMap(int xLoc, int yLoc) // prints only player mini map
{
    if(xLoc >= 3 && xLoc <= 21 && yLoc >= 3 && yLoc <= 12) // player location is not near any edges
    {
        for(int i = xLoc - 3; i <= xLoc + 3; i++)
        {
            for(int j = yLoc - 3; j <= yLoc + 3; j++) 
            {
                cout << map[i][j].getType() << " ";
            } 
            
            cout << endl;
        }
    }                                                          // each check sees if any x or y value of the players location will be negative or above the upper bounds of the rows and colums when 3 is added or subtracted
    if((xLoc - 3) < 0 && xLoc <= 22 && yLoc >= 3 && yLoc <= 12) // Top edge check 
    {
        for(int i = 0; i <= xLoc + 3; i++)
        {
            for(int j = yLoc - 3; j <= yLoc + 3; j++) 
            {
                cout << map[i][j].getType() << " ";
            } 
            
            cout << endl;
        }
    }
    if(xLoc >= 3 && (xLoc + 3) > 24 && yLoc >= 3 && yLoc <= 12) // Bottom edge check
    {
        for(int i = xLoc - 3; i <= 24; i++)
        {
            for(int j = yLoc - 3; j <= yLoc + 3; j++) 
            {
                cout << map[i][j].getType() << " ";
            } 
            
            cout << endl;
        }
    }
    if(xLoc >= 3 && xLoc <= 21 && (yLoc - 3) < 0 && yLoc <= 12) // left side check
    {
        for(int i = xLoc - 3; i <= xLoc + 3; i++)
        {
            for(int j = 0; j <= yLoc + 3; j++) 
            {
                cout << map[i][j].getType() << " ";
            } 
            
            cout << endl;
        }
    }
    if(xLoc >= 3 && xLoc <= 21 && yLoc >= 3 && (yLoc + 3) > 15) // right side check
    {
        for(int i = xLoc - 3; i <= xLoc + 3; i++)
        {
            for(int j = yLoc - 3; j <= 15; j++) 
            {
                cout << map[i][j].getType() << " ";
            } 
            
            cout << endl;
        }
    }
    if((xLoc - 3) < 0 && xLoc <= 22 && (yLoc - 3) < 0 && yLoc <= 12) // Top-left corner check
    {
        for(int i = 0; i <= xLoc + 3; i++)
        {
            for(int j = 0; j <= yLoc + 3; j++) 
            {
                cout << map[i][j].getType() << " ";
            } 
            
            cout << endl;
        }
    }
    if((xLoc - 3) < 0 && xLoc <= 22 && yLoc >= 3 && (yLoc + 3) > 15) // Top-right corner check
    {
        for(int i = 0; i <= xLoc + 3; i++)
        {
            for(int j = yLoc - 3; j <= 15; j++) 
            {
                cout << map[i][j].getType() << " ";
            } 
            
            cout << endl;
        }
    }
    if(xLoc >= 3 && (xLoc + 3) > 24 && (yLoc - 3) < 0 && yLoc <= 12) // Bottom-left corner check
    {
        for(int i = xLoc - 3; i <= 24; i++)
        {
            for(int j = 0; j <= yLoc + 3; j++) 
            {
                cout << map[i][j].getType() << " ";
            } 
            
            cout << endl;
        }
    }
    if(xLoc >= 3 && (xLoc + 3) > 24 && yLoc >= 3 && (yLoc + 3) > 15) // Bottom-right corner check
    {
        for(int i = xLoc - 3; i <= 24; i++)
        {
            for(int j = yLoc - 3; j <= 15; j++) 
            {
                cout << map[i][j].getType() << " ";
            } 
            
            cout << endl;
        }
    }
    
}

Pokemon Game::tryLuck(int xLoc, int yLoc)
{
    srand(time(NULL));
    
    int count = 0;
    
    if(xLoc >= 3 && xLoc <= 21 && yLoc >= 3 && yLoc <= 12) // player location is not near any edges
    {
        for(int i = xLoc - 3; i <= xLoc + 3; i++)
        {
            for(int j = yLoc - 3; j <= yLoc + 3; j++) 
            {
                if(map[i][j].checkPokemon() == true)
                {
                    int randomInt = rand() % 100 + 1; // random number between 1 and 100
                    if(randomInt > 50) // player catches pokemon
                    {
                        Pokemon newPokemon = map[i][j].getTilePokemon();
                        string newPokemonName = newPokemon.getName();
                        int idx = findPokemonPositionInMapVec(newPokemonName);
                        pokemonOnMap.erase(pokemonOnMap.begin() + idx);
                        map[i][j].setPokemonTile(false);
                        
                        return newPokemon;
                        
                    }
                    if(randomInt < 50) // player doesn't catch pokemon
                    {
                        Pokemon newPokemon;
                        newPokemon.setName("didn't catch");
                        return newPokemon;
                    }
                }
                else if(map[i][j].checkPokemon() == false)
                {
                    count++;
                }
                if(count == 48)
                {
                    Pokemon newPokemon;
                    newPokemon.setName("didn't catch");
                    return newPokemon;
                }
                
            } 
            
        }
    }
    if((xLoc - 3) < 0 && xLoc <= 22 && yLoc >= 3 && yLoc <= 12) // Top edge check //////////////////////////////
    {
        for(int i = 0; i <= xLoc + 3; i++)
        {
            for(int j = yLoc - 3; j <= yLoc + 3; j++) 
            {
                if(map[i][j].checkPokemon() == true)
                {
                    int randomInt = rand() % 100 + 1; // random number between 1 and 100
          
                    if(randomInt > 50) // player catches pokemon
                    {
                        Pokemon newPokemon = map[i][j].getTilePokemon();
                        string newPokemonName = newPokemon.getName();
                        int idx = findPokemonPositionInMapVec(newPokemonName);
                        pokemonOnMap.erase(pokemonOnMap.begin() + idx);
                        map[i][j].setPokemonTile(false);
              
                        return newPokemon;
                        
                    }
                    if(randomInt < 50) // player doesn't catch pokemon
                    {
                        Pokemon newPokemon;
                        newPokemon.setName("didn't catch");
                        return newPokemon;
                    }
                }
                else if(map[i][j].checkPokemon() == false)
                {
                    count++;
                }
                if((xLoc - 3) == -1) // one less row showing
                {
                    int maxTiles = 42;
                    
                    if(count == maxTiles)
                    {
                        Pokemon newPokemon;
                        newPokemon.setName("didn't catch");
                        return newPokemon;
                    }
                }
                
                if((xLoc - 3) == -2) // 2 less rows showing
                {
                    int maxTiles = 35;
                    
                    if(count == maxTiles)
                    {
                        Pokemon newPokemon;
                        newPokemon.setName("didn't catch");
                        return newPokemon;
                    }
                }
                
                if((xLoc - 3) == -3) // 3 less rows showing
                {
                    int maxTiles = 28;
                    
                    if(count == maxTiles)
                    {
                        Pokemon newPokemon;
                        newPokemon.setName("didn't catch");
                        return newPokemon;
                    }
                }
            } 
            
            cout << endl;
        }
    }
    if(xLoc >= 3 && (xLoc + 3) > 24 && yLoc >= 3 && yLoc <= 12) // Bottom edge check
    {
        for(int i = xLoc - 3; i <= 24; i++)
        {
            for(int j = yLoc - 3; j <= yLoc + 3; j++) 
            {
                if(map[i][j].checkPokemon() == true)
                {
                    int randomInt = rand() % 100 + 1; // random number between 1 and 100
               
                    if(randomInt > 50) // player catches pokemon
                    {
                        Pokemon newPokemon = map[i][j].getTilePokemon();
                        string newPokemonName = newPokemon.getName();
                        int idx = findPokemonPositionInMapVec(newPokemonName);
                        pokemonOnMap.erase(pokemonOnMap.begin() + idx);
                        map[i][j].setPokemonTile(false);
                  
                        return newPokemon;
                        
                    }
                    if(randomInt < 50) // player doesn't catch pokemon
                    {
                        Pokemon newPokemon;
                        newPokemon.setName("didn't catch");
                        return newPokemon;
                    }
                }
                else if(map[i][j].checkPokemon() == false)
                {
                    count++;
                }
                if((xLoc + 3) == 25) // one less row showing
                {
                    int maxTiles = 42;
                    
                    if(count == maxTiles)
                    {
                        Pokemon newPokemon;
                        newPokemon.setName("didn't catch");
                        return newPokemon;
                    }
                }
                
                if((xLoc + 3) == 26) // 2 less rows showing
                {
                    int maxTiles = 35;
                    
                    if(count == maxTiles)
                    {
                        Pokemon newPokemon;
                        newPokemon.setName("didn't catch");
                        return newPokemon;
                    }
                }
                
                if((xLoc + 3) == 27) // 3 less rows showing
                {
                    int maxTiles = 28;
                    
                    if(count == maxTiles)
                    {
                        Pokemon newPokemon;
                        newPokemon.setName("didn't catch");
                        return newPokemon;
                    }
                }
            } 
            
            cout << endl;
        }
    }
    if(xLoc >= 3 && xLoc <= 21 && (yLoc - 3) < 0 && yLoc <= 12) // left side check
    {
        for(int i = xLoc - 3; i <= xLoc + 3; i++)
        {
            for(int j = 0; j <= yLoc + 3; j++) 
            {
                if(map[i][j].checkPokemon() == true)
                {
                    int randomInt = rand() % 100 + 1; // random number between 1 and 100
                    if(randomInt > 50) // player catches pokemon
                    {
                        Pokemon newPokemon = map[i][j].getTilePokemon();
                        string newPokemonName = newPokemon.getName();
                        int idx = findPokemonPositionInMapVec(newPokemonName);
                        pokemonOnMap.erase(pokemonOnMap.begin() + idx);
                        map[i][j].setPokemonTile(false);
                        
                        return newPokemon;
                        
                    }
                    if(randomInt < 50) // player doesn't catch pokemon
                    {
                        Pokemon newPokemon;
                        newPokemon.setName("didn't catch");
                        return newPokemon;
                    }
                }
                else if(map[i][j].checkPokemon() == false)
                {
                    count++;
                }
                if((yLoc - 3) == -1) // one less column showing
                {
                    int maxTiles = 42;
                    
                    if(count == maxTiles)
                    {
                        Pokemon newPokemon;
                        newPokemon.setName("didn't catch");
                        return newPokemon;
                    }
                }
                
                if((yLoc - 3) == -2) // 2 less columns showing
                {
                    int maxTiles = 35;
                    
                    if(count == maxTiles)
                    {
                        Pokemon newPokemon;
                        newPokemon.setName("didn't catch");
                        return newPokemon;
                    }
                }
                
                if((yLoc - 3) == -3) // 3 less columns showing
                {
                    int maxTiles = 28;
                    
                    if(count == maxTiles)
                    {
                        Pokemon newPokemon;
                        newPokemon.setName("didn't catch");
                        return newPokemon;
                    }
                }
            } 
            
            cout << endl;
        }
    }
    if(xLoc >= 3 && xLoc <= 21 && yLoc >= 3 && (yLoc + 3) > 15) // right side check
    {
        for(int i = xLoc - 3; i <= xLoc + 3; i++)
        {
            for(int j = yLoc - 3; j <= 15; j++) 
            {
                if(map[i][j].checkPokemon() == true)
                {
                    int randomInt = rand() % 100 + 1; // random number between 1 and 100
            
                    if(randomInt > 50) // player catches pokemon
                    {
                        Pokemon newPokemon = map[i][j].getTilePokemon();
                        string newPokemonName = newPokemon.getName();
                        int idx = findPokemonPositionInMapVec(newPokemonName);
                        pokemonOnMap.erase(pokemonOnMap.begin() + idx);
                        map[i][j].setPokemonTile(false);
                       
                        return newPokemon;
                        
                    }
                    if(randomInt < 50) // player doesn't catch pokemon
                    {
                        Pokemon newPokemon;
                        newPokemon.setName("didn't catch");
                        return newPokemon;
                    }
                }
                else if(map[i][j].checkPokemon() == false)
                {
                    count++;
                }
                if((yLoc + 3) == 16) // one less column showing
                {
                    int maxTiles = 42;
                    
                    if(count == maxTiles)
                    {
                        Pokemon newPokemon;
                        newPokemon.setName("didn't catch");
                        return newPokemon;
                    }
                }
                
                if((yLoc + 3) == 17) // 2 less columns showing
                {
                    int maxTiles = 35;
                    
                    if(count == maxTiles)
                    {
                        Pokemon newPokemon;
                        newPokemon.setName("didn't catch");
                        return newPokemon;
                    }
                }
                
                if((yLoc + 3) == 18) // 3 less columns showing
                {
                    int maxTiles = 28;
                    
                    if(count == maxTiles)
                    {
                        Pokemon newPokemon;
                        newPokemon.setName("didn't catch");
                        return newPokemon;
                    }
                }
            } 
            
            cout << endl;
        }
    }
    if((xLoc - 3) < 0 && xLoc <= 22 && (yLoc - 3) < 0 && yLoc <= 12) // Top-left corner check
    {
        for(int i = 0; i <= xLoc + 3; i++)
        {
            for(int j = 0; j <= yLoc + 3; j++) 
            {
                if(map[i][j].checkPokemon() == true)
                {
                    int randomInt = rand() % 100 + 1; // random number between 1 and 100
                  
                    if(randomInt > 50) // player catches pokemon
                    {
                        Pokemon newPokemon = map[i][j].getTilePokemon();
                        string newPokemonName = newPokemon.getName();
                        int idx = findPokemonPositionInMapVec(newPokemonName);
                        pokemonOnMap.erase(pokemonOnMap.begin() + idx);
                        map[i][j].setPokemonTile(false);
                        
                        return newPokemon;
                        
                    }
                    if(randomInt < 50) // player doesn't catch pokemon
                    {
                        Pokemon newPokemon;
                        newPokemon.setName("didn't catch");
                        return newPokemon;
                    }
                }
                else if(map[i][j].checkPokemon() == false)
                {
                    count++;
                }
                if((xLoc - 3) == -1 && (yLoc - 3) == -1) // 6x6 grid
                {
                    int maxTiles = 36;
                    
                    if(count == maxTiles)
                    {
                        Pokemon newPokemon;
                        newPokemon.setName("didn't catch");
                        return newPokemon;
                    }
                }
                
                if((xLoc - 3) == -2) ////////////////////////////////////////////////////////////////////
                {
                    int maxTiles = 35;
                    
                    if(count == maxTiles)
                    {
                        Pokemon newPokemon;
                        newPokemon.setName("didn't catch");
                        return newPokemon;
                    }
                }
                
                if((xLoc - 3) == -3)
                {
                    int maxTiles = 28;
                    
                    if(count == maxTiles)
                    {
                        Pokemon newPokemon;
                        newPokemon.setName("didn't catch");
                        return newPokemon;
                    }
                }
            } 
            
            cout << endl;
        }
    }
    if((xLoc - 3) < 0 && xLoc <= 22 && yLoc >= 3 && (yLoc + 3) > 15) // Top-right corner check
    {
        for(int i = 0; i <= xLoc + 3; i++)
        {
            for(int j = yLoc - 3; j <= 15; j++) 
            {
                cout << map[i][j].getType() << " ";
            } 
            
            cout << endl;
        }
    }
    if(xLoc >= 3 && (xLoc + 3) > 24 && (yLoc - 3) < 0 && yLoc <= 12) // Bottom-left corner check
    {
        for(int i = xLoc - 3; i <= 24; i++)
        {
            for(int j = 0; j <= yLoc + 3; j++) 
            {
                cout << map[i][j].getType() << " ";
            } 
            
            cout << endl;
        }
    }
    if(xLoc >= 3 && (xLoc + 3) > 24 && yLoc >= 3 && (yLoc + 3) > 15) // Bottom-right corner check
    {
        for(int i = xLoc - 3; i <= 24; i++)
        {
            for(int j = yLoc - 3; j <= 15; j++) 
            {
                cout << map[i][j].getType() << " ";
            } 
            
            cout << endl;
        }
    }   

    return Pokemon();
}

void Game::updateScores(string name, int points) // update scores at the end of the game
{
    
}

Tile Game::nearbyCheck(int xLoc, int yLoc) // checks for nearby pokemon
{
    bool nearby = false;
    
    if(xLoc >= 2 && xLoc <= 22 && yLoc >= 2 && yLoc <= 13) // player location is not near any edges
    {
        for(int i = xLoc - 2; i <= xLoc + 2; i++)
        {
            for(int j = yLoc - 2; j <= yLoc + 2; j++) 
            {
                bool nearby = map[i][j].checkPokemon();
                if(nearby == 1)
                {
                    Tile newTile = map[i][j];
                    return newTile;
                }
            } 
        }
    }                                                          // each check sees if any x or y value of the players location will be negative or above the upper bounds of the rows and colums when 3 is added or subtracted
    if((xLoc - 2) < 0 && xLoc <= 22 && yLoc >= 2 && yLoc <= 13) // Top edge check 
    {
        for(int i = 0; i <= xLoc + 2; i++)
        {
            for(int j = yLoc - 2; j <= yLoc + 2; j++) 
            {
                bool nearby = map[i][j].checkPokemon();
                if(nearby == 1)
                {
                    Tile newTile = map[i][j];
                    return newTile;
                }
            } 
        }
    }
    if(xLoc >= 2 && (xLoc + 2) > 24 && yLoc >= 2 && yLoc <= 13) // Bottom edge check
    {
        for(int i = xLoc - 2; i <= 24; i++)
        {
            for(int j = yLoc - 2; j <= yLoc + 2; j++) 
            {
                bool nearby = map[i][j].checkPokemon();
                if(nearby == 1)
                {
                    Tile newTile = map[i][j];
                    return newTile;
                }
            } 
        }
    }
    if(xLoc >= 2 && xLoc <= 22 && (yLoc - 2) < 0 && yLoc <= 13) // left side check
    {
        for(int i = xLoc - 2; i <= xLoc + 2; i++)
        {
            for(int j = 0; j <= yLoc + 2; j++) 
            {
                bool nearby = map[i][j].checkPokemon();
                if(nearby == 1)
                {
                    Tile newTile = map[i][j];
                    return newTile;
                }
            } 
            
        }
    }
    if(xLoc >= 32 && xLoc <= 22 && yLoc >= 2 && (yLoc + 2) > 15) // right side check
    {
        for(int i = xLoc - 2; i <= xLoc + 2; i++)
        {
            for(int j = yLoc - 2; j <= 15; j++) 
            {
                bool nearby = map[i][j].checkPokemon();
                if(nearby == 1)
                {
                    Tile newTile = map[i][j];
                    return newTile;
                }
            } 
            
        }
    }
    if((xLoc - 2) < 0 && xLoc <= 22 && (yLoc - 2) < 0 && yLoc <= 13) // Top-left corner check
    {
        for(int i = 0; i <= xLoc + 2; i++)
        {
            for(int j = 0; j <= yLoc + 2; j++) 
            {
                bool nearby = map[i][j].checkPokemon();
                if(nearby == 1)
                {
                    Tile newTile = map[i][j];
                    return newTile;
                }
            } 
            
        }
    }
    if((xLoc - 2) < 0 && xLoc <= 22 && yLoc >= 2 && (yLoc + 2) > 15) // Top-right corner check
    {
        for(int i = 0; i <= xLoc + 2; i++)
        {
            for(int j = yLoc - 2; j <= 15; j++) 
            {
                bool nearby = map[i][j].checkPokemon();
                if(nearby == 1)
                {
                    Tile newTile = map[i][j];
                    return newTile;
                }
            } 
            
        }
    }
    if(xLoc >= 2 && (xLoc + 2) > 24 && (yLoc - 2) < 0 && yLoc <= 13) // Bottom-left corner check
    {
        for(int i = xLoc - 2; i <= 24; i++)
        {
            for(int j = 0; j <= yLoc + 2; j++) 
            {
                bool nearby = map[i][j].checkPokemon();
                if(nearby == 1)
                {
                    Tile newTile = map[i][j];
                    return newTile;
                }
            } 
        }
    }
    if(xLoc >= 2 && (xLoc + 2) > 24 && yLoc >= 3 && (yLoc + 2) > 15) // Bottom-right corner check
    {
        for(int i = xLoc - 2; i <= 24; i++)
        {
            for(int j = yLoc - 2; j <= 15; j++) 
            {
                bool nearby = map[i][j].checkPokemon();
                if(nearby == 1)
                {
                    Tile newTile = map[i][j];
                    return newTile;
                }
            } 
        }
    }
    
    
    Tile errorTile;
    errorTile.makeType('E');
    return errorTile;
    
    
}

Tile Game::luckCheck(int xLoc, int yLoc)
{
    bool nearby = false;
    
    if(xLoc >= 3 && xLoc <= 21 && yLoc >= 3 && yLoc <= 12) // player location is not near any edges
    {
        for(int i = xLoc - 3; i <= xLoc + 3; i++)
        {
            for(int j = yLoc - 3; j <= yLoc + 3; j++) 
            {
                bool nearby = map[i][j].checkPokemon();
                if(nearby == 1)
                {
                    Tile newTile = map[i][j];
                    return newTile;
                }
            } 
        }
    }                                                          // each check sees if any x or y value of the players location will be negative or above the upper bounds of the rows and colums when 3 is added or subtracted
    if((xLoc - 3) < 0 && xLoc <= 22 && yLoc >= 3 && yLoc <= 12) // Top edge check 
    {
        for(int i = 0; i <= xLoc + 3; i++)
        {
            for(int j = yLoc - 3; j <= yLoc + 3; j++) 
            {
                bool nearby = map[i][j].checkPokemon();
                if(nearby == 1)
                {
                    Tile newTile = map[i][j];
                    return newTile;
                }
            } 
        }
    }
    if(xLoc >= 3 && (xLoc + 3) > 24 && yLoc >= 3 && yLoc <= 12) // Bottom edge check
    {
        for(int i = xLoc - 3; i <= 24; i++)
        {
            for(int j = yLoc - 3; j <= yLoc + 3; j++) 
            {
                bool nearby = map[i][j].checkPokemon();
                if(nearby == 1)
                {
                    Tile newTile = map[i][j];
                    return newTile;
                }
            } 
        }
    }
    if(xLoc >= 3 && xLoc <= 21 && (yLoc - 3) < 0 && yLoc <= 12) // left side check
    {
        for(int i = xLoc - 3; i <= xLoc + 3; i++)
        {
            for(int j = 0; j <= yLoc + 3; j++) 
            {
                bool nearby = map[i][j].checkPokemon();
                if(nearby == 1)
                {
                    Tile newTile = map[i][j];
                    return newTile;
                }
            } 
        }
    }
    if(xLoc >= 3 && xLoc <= 21 && yLoc >= 3 && (yLoc + 3) > 15) // right side check
    {
        for(int i = xLoc - 3; i <= xLoc + 3; i++)
        {
            for(int j = yLoc - 3; j <= 15; j++) 
            {
                bool nearby = map[i][j].checkPokemon();
                if(nearby == 1)
                {
                    Tile newTile = map[i][j];
                    return newTile;
                }
            }
        }
    }
    if((xLoc - 3) < 0 && xLoc <= 22 && (yLoc - 3) < 0 && yLoc <= 12) // Top-left corner check
    {
        for(int i = 0; i <= xLoc + 3; i++)
        {
            for(int j = 0; j <= yLoc + 3; j++) 
            {
                bool nearby = map[i][j].checkPokemon();
                if(nearby == 1)
                {
                    Tile newTile = map[i][j];
                    return newTile;
                }
            } 
        }
    }
    if((xLoc - 3) < 0 && xLoc <= 22 && yLoc >= 3 && (yLoc + 3) > 15) // Top-right corner check
    {
        for(int i = 0; i <= xLoc + 3; i++)
        {
            for(int j = yLoc - 3; j <= 15; j++) 
            {
               bool nearby = map[i][j].checkPokemon();
                if(nearby == 1)
                {
                    Tile newTile = map[i][j];
                    return newTile;
                }
            } 
        }
    }
    if(xLoc >= 3 && (xLoc + 3) > 24 && (yLoc - 3) < 0 && yLoc <= 12) // Bottom-left corner check
    {
        for(int i = xLoc - 3; i <= 24; i++)
        {
            for(int j = 0; j <= yLoc + 3; j++) 
            {
                bool nearby = map[i][j].checkPokemon();
                if(nearby == 1)
                {
                    Tile newTile = map[i][j];
                    return newTile;
                }
            } 
            
        }
    }
    if(xLoc >= 3 && (xLoc + 3) > 24 && yLoc >= 3 && (yLoc + 3) > 15) // Bottom-right corner check
    {
        for(int i = xLoc - 3; i <= 24; i++)
        {
            for(int j = yLoc - 3; j <= 15; j++) 
            {
                bool nearby = map[i][j].checkPokemon();
                if(nearby == 1)
                {
                    Tile newTile = map[i][j];
                    return newTile;
                }
            } 
        
        }
    }
    
    
    Tile errorTile;
    errorTile.makeType('E');
    return errorTile;            
    
}

int Game::pokemonEncounter(Pokemon encounteredPokemon, Pokemon current)
{
    srand(time(NULL));
    cout << "You ran into a wild Pokemon!" << endl;
    cout << "Name: " << encounteredPokemon.getName() << ", HP: " << encounteredPokemon.getHP();
    cout << ", A: " << encounteredPokemon.getAttack() << ", D: " << encounteredPokemon.getDefense(); 
    cout << ", S: " << encounteredPokemon.getSpeed() << ", M: " << encounteredPokemon.getMax() << endl;
    cout << endl;
    cout << "Your ACTIVE Pokemon is: " << endl;
    cout << "Name: " << current.getName() << ", HP: " << current.getHP();
    cout << ", A: " << current.getAttack() << ", D: " << current.getDefense(); 
    cout << ", S: " << current.getSpeed() << ", M: " << current.getMax() << endl;
    cout << endl;
    cout << "What do you want to do (pick 1, 2, or 3):" << endl;
    cout << "   1. Fight" << endl;
    cout << "   2. Switch Active Pokemon" << endl;
    cout << "   3. Run" << endl;
    string input;
    getline(cin, input);
    if(input == "1") // fight
    {
        if(current.getHP() <= 0)
        {
            cout << "Your Pokemon has fainted and cannot fight.  Choose a different Pokemon." << endl;
            return 6;
        }
        if(numEncounters < 2) // first 2 pokemon the player has encountered
        {
            cout << "Since you have very few Pokemon, " << encounteredPokemon.getName() << " will join your active party." << endl;
            cout << endl;
            int idx = findPokemonPositionInMapVec(encounteredPokemon.getName()); 
            pokemonOnMap.erase(pokemonOnMap.begin() + idx);
            
            numEncounters++;
            return 1; // return 1 so the pokemon can be added to the players active party in the game driver
        }
        else
        {
            int random = rand() % 100 + 1;
            if(random > 60)
            {
                int wildSpeed = encounteredPokemon.getSpeed();
                int yourSpeed = (current.getSpeed() / 4) % 256;
                int escapeAttempts = 1; 
                int escapeResult = ((wildSpeed * 32)/yourSpeed) + 30 * escapeAttempts; // formula for escape
                if(escapeResult > 255)
                {
                    cout << "Oh no! " << encounteredPokemon.getName() << " has escaped!" << endl; 
                    numEncounters++;
                    return 0;
                }
                if(escapeResult <= 255)
                {
                    int newRand = rand() % 255 + 0;
                    if(newRand < escapeResult)
                    {
                        cout << "Oh no! " << encounteredPokemon.getName() << " has escaped!" << endl;
                        numEncounters++;
                        return 0;
                    }
                    else
                    {
                        random = 1; // if they don't escape, a fight will happen
                    }
                }
                
            }
            if(random <= 60)
            {
                return 4;
                
            }
            
        }
        
    }
    if(input == "2")
    {
        return 6;
    }
    if(input == "3")
    {
        int yourSpeed = current.getSpeed();
        int wildSpeed = (encounteredPokemon.getSpeed() / 4) % 256;
        int escapeAttempts = 1; 
        int escapeResult = ((yourSpeed * 32)/wildSpeed) + 30 * escapeAttempts; // formula for escape
        if(wildSpeed < yourSpeed)
        {
            cout << "You escape!" << endl;
            return 7;
        }
        if(escapeResult > 255)
        {
            cout << "You escape!" << endl;
            return 7;
        }
        if(escapeResult <= 255)
        {
            int random2 = rand() % 255 + 0;
            if(random2 < escapeResult)
            {
                cout << "You escape!" << endl;
                return 7;
            }
            else
            {
                cout << "You couldn't escape." << endl;
                return 2;
            }
        }
    }

    return 0;
    
}

void Game::pokemonCenter()
{
    
}

int Game::movePlayer(int direction, int x, int y) // Moves player up, down, left or right
{
    if(direction == 1)                                                               // north
    {
        if(map[x - 1][y].getType() != '~' && (x - 1) >= 0 && (x - 1) <= 24)
        {
            map[x - 1][y].makeType('@');
            map[x][y].makeType('*');
            return 1;
        }
        else
        {
            cout << "You can't move there.  Choose a different direction." << endl;
            return -1;
        }
    }
    if(direction == 2)                                                         // east
    {
        if(map[x][y + 1].getType() != '~' && (y + 1) >= 0 && (y + 1) <= 15)
        {
            map[x][y + 1].makeType('@');
            map[x][y].makeType('*');
            return 1;
        }
        else
        {
            cout << "You can't move there.  Choose a different direction." << endl;
            return -1;
        }
    }
    if(direction == 3)                                                           // south
    {
        if(map[x + 1][y].getType() != '~' && (x + 1) >= 0 && (x + 1) <= 24)
        {
            map[x + 1][y].makeType('@');
            map[x][y].makeType('*');
            return 1;
        }
        else
        {
            cout << "You can't move there.  Choose a different direction." << endl;
            return -1;
        }
    }
    if(direction == 4)                                                      // west
    {
        if(map[x][y - 1].getType() != '~' && (y - 1) >= 0 && (y - 1) <= 15)
        {
            map[x][y - 1].makeType('@');
            map[x][y].makeType('*');
            return 1;
        }
        else
        {
            cout << "You can't move there.  Choose a different direction." << endl;     // the tile is either water or out of bounds
            return -1;
        }
    }

    return -1;
}

void Game::PokemonShift()
{
    srand(time(NULL));
    
    for(int i = 0; i < pokemonOnMap.size(); i++)
    {
        int currentX = pokemonOnMap.at(i).getX();
        int currentY = pokemonOnMap.at(i).getY();
        int x;
        int y;
        bool moved = false;
        while(moved == false)
        {
            int direction = rand() % 4 + 1; // random number 1 through 4
            if(direction == 1) // north
            {
                x = currentX - 1;
                y = currentY;
            }
            if(direction == 2) // east
            {
                x = currentX;
                y = currentY + 1;
            }
            if(direction == 3) // south
            {
                x = currentX + 1;
                y = currentY;
            }
            if(direction == 4) // west
            {
                x = currentX;
                y = currentY - 1;
            }
            
            if(map[x][y].getType() != 'C' && map[x][y].getType() != 'G' && map[x][y].getType() != '@' && map[x][y].getType() != '~' && map[x][y].checkPokemon() != 1 && x >= 0 && x <= 24 && y >= 0 && y <= 15)
            {
                map[x][y].setPokemonTile(true); // new tile
                map[currentX][currentY].setPokemonTile(false); // old tile
                pokemonOnMap.at(i).setX(x);
                pokemonOnMap.at(i).setY(y);
                map[x][y].placePokemonOnTile(pokemonOnMap.at(i));
                moved = true; // stops the loop in the next iteration because the pokemon has been shifted
            }
        }
        
    }
}

int Game::randomPokemonSpawn()
{
    srand(time(NULL));
    int chance = rand() % 100 + 1;
    if(chance > 30)
    {
        return 0;
    }
    if(chance < 30)
    {
        return 1;
    }

    return -1;
}

void Game::removePokemonFromMapVec(int idx)
{
    wildPokemon.erase(wildPokemon.begin() + idx);
}

void Game::battle(Pokemon fighters[2])
{
     int wildSpeed = fighters[0].getSpeed(); // to determine which pokemon will attack first
                int yourSpeed = fighters[1].getSpeed();
                if(wildSpeed > yourSpeed) // wild pokemon attacks first
                {
                    int A = rand() % fighters[0].getAttack() + 0;
                    int D = rand() % fighters[1].getDefense() + 0;
                    cout << fighters[0].getName() << " attacks!" << endl;
                    if(A > D)
                    {
                        int hp = fighters[1].getHP();
                        cout << fighters[0].getName() << " deals " << (A-D) << " damage." << endl;
                        hp = hp - (A - D);
                        fighters[1].setHP(hp);
                        
                    }
                    if(A <= D)
                    {
                        cout <<fighters[0].getName() << " deals 0 damage." << endl;
                    }
                    if(fighters[1].getHP() <= 0)
                    {
                        fighters[1].setHP(0);
                    }
                    
                    fighters[0].displayPokemonStats();
                    fighters[1].displayPokemonStats();
                    cout << endl;
                    
                    int A2 = rand() % fighters[0].getDefense() + 0; // next pokemon's turn to attack
                    int D2 = rand() % fighters[1].getAttack() + 0;
                    cout << fighters[1].getName() << " attacks!" << endl;
                    if(A2 > D2)
                    {
                        int hp = fighters[0].getHP(); // original hp
                        cout << fighters[1].getName() << " deals " << (A2-D2) << " damage." << endl;
                        hp = hp - (A2 - D2);
                        fighters[0].setHP(hp);
                        
                    }
                    if(A2 <= D2)
                    {
                        cout << fighters[1].getName() << " deals 0 damage." << endl;
                    }
                    if(fighters[0].getHP() <= 0)
                    {
                        fighters[0].setHP(0);
                    }
        
                    fighters[0].displayPokemonStats();
                    fighters[1].displayPokemonStats();
                    cout << endl;
                }
                
                if(wildSpeed < yourSpeed) // player's pokemon attacks first
                {
                    int A = rand() % fighters[1].getAttack() + 0;
                    int D = rand() % fighters[0].getDefense() + 0;
                    cout << fighters[1].getName() << " attacks!" << endl;
                    if(A > D)
                    {
                        int hp = fighters[0].getHP(); // oringal hp
                        cout << fighters[1].getName() << " deals " << (A-D) << " damage." << endl;
                        hp = hp - (A - D);
                        fighters[0].setHP(hp);
                        
                    }
                    if(A <= D)
                    {
                        cout << fighters[1].getName() << " deals 0 damage." << endl;
                    }
                    if(fighters[0].getHP() <= 0)
                    {
                        fighters[0].setHP(0);
                    }
                   
                
                    fighters[0].displayPokemonStats();
                    fighters[1].displayPokemonStats();
                    cout << endl;
                    
                    int A2 = rand() % fighters[1].getDefense() + 0;
                    int D2 = rand() % fighters[0].getAttack() + 0;
                    cout << fighters[0].getName() << " attacks!" << endl;
                    if(A2 > D2)
                    {
                        int hp = fighters[1].getHP();
                        cout << fighters[0].getName() << " deals " << (A2-D2) << " damage." << endl;
                        hp = hp - (A2 - D2);
                        fighters[1].setHP(hp);

                    }
                    if(A2 <= D2)
                    {
                        cout << fighters[0].getName() << " deals 0 damage." << endl;
                    }
                    if(fighters[1].getHP() <= 0)
                    {
                        fighters[1].setHP(0);
                    }
                   
                    fighters[0].displayPokemonStats();
                    fighters[1].displayPokemonStats();
                    cout << endl;
                    
                    
                    
                }

}