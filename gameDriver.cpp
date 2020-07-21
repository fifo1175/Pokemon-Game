#include <string>
#include <vector>
#include <fstream>
#include <cctype>
#include <math.h>
#include <cmath>
#include <ctime>
#include "Tile.h"
#include "Gym.h"
#include "Pokemon.h"
#include "Player.h"
#include "Game.h"
using namespace std;

int main()
{ 
    // START OF GAME
    
    Tile map1[24][15];
    
    vector <Pokemon> emptyPokemon = {};
    
    Game g1(map1, 25, 16, emptyPokemon, 0); // construct game object
    
    g1.readPokemon(151, "pokemon.txt"); // read pokemon file
    
    g1.readMap("map.txt"); // read map file
    
    
    string playerName;
    
    cout << endl;
    
    cout << "Welcome to Pokemon!" << endl;
    
    cout << endl;
    
    cout << "What is your name? " << endl;
    
    getline(cin, playerName);
    
    Player p1; // make new player object
    
    p1.setPlayerName(playerName); // set their name
    
    cout << "Welcome, " << playerName << "! Before beginning your" << endl << "adventure, you must choose a starting Pokemon." << endl;
    cout << "Choose from the following Pokemon: " << endl;
    cout << endl;
    
    cout << "1. Bulbasaur" << endl;
    cout << "2. Charmander" << endl;
    cout << "3. Squirtle" << endl;
    cout << "4. Pikachu" << endl;
    int error = 0;
    Pokemon starter;
    while(error == 0)
    {
        string choice;
        getline(cin, choice);
        int input = stoi(choice);
        switch(input)
        {
            case 1:
                starter = g1.findPokemon("Bulbasaur");
                p1.addPokemonActive(starter);
                
                cout << "Bulbasaur has been added to your current party!" << endl;
                
                g1.placePlayer(12, 7);
                p1.setXLoc(12);
                p1.setYLoc(7);
                error = 1;
                break;
            
            case 2:
                starter = g1.findPokemon("Charmander");
                p1.addPokemonActive(starter);
                
                cout << "Charmander has been added to your current party!" << endl;
                
                g1.placePlayer(12, 8);
                p1.setXLoc(12);
                p1.setYLoc(8);
                error = 1;
                break;
            
            case 3:
                starter = g1.findPokemon("Squirtle");
                p1.addPokemonActive(starter);
                
                cout << "Squirtle has been added to your current party!" << endl;
                
                g1.placePlayer(12, 9);
                p1.setXLoc(12);
                p1.setYLoc(9);
                error = 1;
                break;
                
                
            case 4:
                starter = g1.findPokemon("Pikachu");
                p1.addPokemonActive(starter);
                
                cout << "Pikachu has been added to your current party!" << endl;
                
                g1.placePlayer(12, 10);
                p1.setXLoc(12);
                p1.setYLoc(10);
                error = 1;
                break;
            
            default:
                cout << "Please enter a number 1 through 4." << endl;
                break;
        }
        
        
    }
    
    cout << endl;
    
    g1.scatterPokemon(); // scatter 20 random pokemon across the map
    
    int input;
    
    while(input != 4) // new turn, show player their pokemon, pokeballs and their 4 options
    {
        g1.printPlayerMap(p1.getXLoc(), p1.getYLoc()); // print the player's minimap using their x and y coordinates
        
        cout << "The sun is shining, " << p1.getName() << "!  ";
        cout << "You have " << p1.getPokeballs() << " pokeballs left and your Pokemon are strong." << endl;
        cout << endl;
        for(int i = 0; i < p1.getNumActivePokemon(); i++) // display Player's current pokemon and stats
        {
            Pokemon display = p1.getActivePokemon(i);
            display.displayPokemonStats();
        }
        cout << endl;
        cout << "Please choose from the following options: " << endl;
        cout << endl;
        cout << "1. Travel" << endl;
        cout << "2. Rest" << endl;
        cout << "3. Try your luck" << endl;
        cout << "4. Quit the game" << endl;
        
        
        int direction; // variables to be used in switch cases (causes errors if declared inside cases)
        int move;
        int move2;
        string dString;
        int direction2;
        Tile checkTile;
        Pokemon checkPokemon;
        int isPokemoninMapVec;
        Pokemon pokemonLuck;
        int checkError = 0;
        while(checkError == 0)
        {
            string s1; 
            getline(cin, s1);
            input = stoi(s1);
            switch(input)
            {
                case 1:
                    cout << "In which direction would you like to travel?" << endl;
                    cout << "1. North" << endl;
                    cout << "2. East" << endl;
                    cout << "3. South" << endl;
                    cout << "4. West" << endl;
                
                    getline(cin, dString);
                    direction = stoi(dString);
                    move = g1.movePlayer(direction, p1.getXLoc(), p1.getYLoc()); // use the move function with the direction they choose and their coordinates
                    move2 = 5;
                    while(move != 1 && move2 != 1) // if the player could not move, end the loop when they successfully move
                    {
                        cout << "In which direction would you like to travel?" << endl;
                        cout << "1. North" << endl;
                        cout << "2. East" << endl;
                        cout << "3. South" << endl;
                        cout << "4. West" << endl;
                        dString;
                        getline(cin, dString);
                        direction2 = stoi(dString);
                        move2 = g1.movePlayer(direction2, p1.getXLoc(), p1.getYLoc());
                        p1.updateLocation(direction2);
                        
                    }
                    if(move == 1)
                    {
                        p1.updateLocation(direction);
                    }
                    checkError = 1;
                    break;
                    
                case 2:
                    p1.rest();
                    cout << "You feel rested and your Pokemon grow stronger!" << endl;
                    cout << endl;
                    checkError = 1;
                    break;
                    
                case 3:
                    cout << "You try your luck to catch a nearby Pokemon..." << endl;
                    checkTile = g1.luckCheck(p1.getXLoc(), p1.getYLoc());
                    checkPokemon = checkTile.getTilePokemon();
                    isPokemoninMapVec = g1.findPokemonPositionInMapVec(checkPokemon.getName());
                    if(isPokemoninMapVec == 30)
                    {
                        cout << "You couldn't catch any nearby Pokemon.  Unlucky!" << endl;
                    }
                    if(isPokemoninMapVec != 30)
                    {
                        pokemonLuck = g1.tryLuck(p1.getXLoc(), p1.getYLoc()); // use tryLuck function with player's coordinates
                        if(pokemonLuck.getName() == "didn't catch")
                        {
                            cout << "You couldn't catch any nearby Pokemon.  Unlucky!" << endl;
                        }
                        else
                        {
                            cout << "You caught a nearby Pokemon!" << endl;
                            if(p1.getNumActivePokemon() <= 6)
                            {
                                p1.addPokemonActive(pokemonLuck);
                                cout << pokemonLuck.getName() << " has been added to your active party!" << endl;
                            }
                            if(p1.getNumActivePokemon() > 6)
                            {
                                p1.addPokemonPokedex(pokemonLuck);
                                cout << pokemonLuck.getName() << " has been added to your Pokedex!" << endl;
                            }
                        }
                    }
                    checkError = 1;
                    break;
                case 4:
                cout << "Thank you for playing!" << endl;
                return 0;
                
                default:
                    cout << "Please enter a number 1 through 4." << endl;
                    break;
                    
            }
            
        }
        
        
        g1.PokemonShift(); // shifts each pokemon in a random direction by 1 tile
        
        
        checkTile = g1.nearbyCheck(p1.getXLoc(), p1.getYLoc()); // checks for nearby Pokemon within 2 tiles of the player
        if(checkTile.getType() != 'E')
        {
            Pokemon wPokemon = checkTile.getTilePokemon();
            Pokemon current = p1.getCurrentPokemon();
            int isPokemoninMapVec = g1.findPokemonPositionInMapVec(wPokemon.getName());
            if(isPokemoninMapVec != 30)
            {
                int encounterResult = g1.pokemonEncounter(wPokemon, current);
                if(encounterResult == 1)
                {
                    p1.addPokemonActive(wPokemon);
                    checkTile.removePokemonFromTile(); // removing pokemon from tile and map vec
                    checkTile.setPokemonTile(false);
                    g1.removePokemonFromMapVec(isPokemoninMapVec);
                }
                    
                if(encounterResult == 3)
                {
                    current.levelUp();
                    if(p1.getNumActivePokemon() < 6)
                    {
                        p1.addPokemonActive(wPokemon); // add the wild pokemon to the players active party
                    }
                    if(p1.getNumActivePokemon() >= 6)
                    {
                        p1.addPokemonPokedex(wPokemon); // add the wild pokemon to the players pokedex
                    }
                }
                if(encounterResult == 7)
                {
                    // send player to nearest pokemon center
                }
            
                int fainted = 0;
                int count = 0;
                Pokemon returnedPokemon[2] = {wPokemon, p1.getCurrentPokemon()};
                while((encounterResult == 4 && fainted == 0) || (encounterResult == 6 && fainted == 0))
                {
                    
                    if(count > 0)
                    {
                        encounterResult = g1.pokemonEncounter(returnedPokemon[0], returnedPokemon[1]);
                    }
                    
                
                    if(encounterResult == 6)
                    {
                        p1.switchPokemon();
                        returnedPokemon[1] = p1.getCurrentPokemon();
                    }
            
                    
                    if(encounterResult == 4)
                    {
                        int faints = 0;
                        g1.battle(returnedPokemon);
                         // faints
                        if(returnedPokemon[1].getHP() <= 0)
                        {
                            cout << "Oh no!  Your pokemon has fainted!" << endl;
                            returnedPokemon[0].levelUp();
                            checkTile.placePokemonOnTile(returnedPokemon[0]);
                            faints++;
                            if(faints == p1.getNumActivePokemon())
                            {
                                fainted = 1;
                            }
                            
                        }
                         if(returnedPokemon[0].getHP() <= 0)
                        {
                            returnedPokemon[1].levelUp();
                            cout << returnedPokemon[0].getName() << "has fainted!" << endl;
                            fainted = 1;
                        }
                    }
                    count++;
        
                }
                
            }
            
           
        }
        
        int randomSpawn = g1.randomPokemonSpawn();
        if(randomSpawn == 1)
        {
            Pokemon randomPokemon = g1.getRandomPokemon();
            cout << "Suddenly, " << randomPokemon.getName() << " appears in your path.  Do you want to: " << endl;
            cout << "   1. Catch it" << endl;
            cout << "   2. Release it" << endl;
            int error = 0;
            
            while(error == 0)
            {
                string choice;
                getline(cin, choice);
                int input = stoi(choice);
                switch(input)
                {
                    case 1:
                        if(p1.getNumActivePokemon() < 6)
                        {
                            cout << "Awesome! " << randomPokemon.getName() << " will join your active party." << endl;
                            p1.addPokemonActive(randomPokemon);
                        }
                        if(p1.getNumActivePokemon() >= 6)
                        {
                            cout << "Awesome! " << randomPokemon.getName() << " will join your Pokedex." << endl;
                            p1.addPokemonPokedex(randomPokemon);
                        }
                        error = 1;
                        break;
                    case 2: 
                        cout << randomPokemon.getName() << " has been released." << endl;
                        error = 1;
                        break;
                        
                    default:
                        cout << "Invalid option.  Please choose again." << endl;
                    break;
                    
                }
            }
        
        }
    }    
    
}

