//Title: Game.cpp
//Author: Deborah Miller
//Section: 10/14
//Email: d169@umbc.edu
//Date: 9/14/2020
//Description: This is part of the Pirates Project in CMSC 202 @ UMBC
//this is the .cpp for the .h Game class

#include "Game.h"
#include "Ship.h"
#include "Pirate.h"
#include <fstream>
#include <string>

//Game
//default constructor
Game::Game(){
  GameTitle();
  LoadShips();
  LoadPirates();
}

//LoadShips
//loads the ship array with ships
void Game::LoadShips(){
  string cannon;
  string toughness;
  string speed;
  
  ifstream ships(PROJ2_SHIPS);

  //populates the m_ships array with ship's structs
  //that has information from the file of all the ships
  for(int i = 0; i < MAX_SHIPS; i++){
    getline(ships, m_ships[i].m_type, ',');
    getline(ships, cannon, ',');
    m_ships[i].m_cannon = stoi(cannon);
    getline(ships, toughness, ',');
    m_ships[i].m_toughness = stoi(toughness);
    m_ships[i].m_curToughness = stoi(toughness);
    getline(ships, speed, ',');
    m_ships[i].m_speed = stoi(speed);
    getline(ships, m_ships[i].m_desc);    
  }
  cout << MAX_SHIPS << " ships loaded." << endl;
}

//LoadPirates
//loads the pirate array with pirate classes
void Game::LoadPirates(){
  string name;
  string rating;
  string origin;
  string desc;
  
  ifstream pirates(PROJ2_PIRATES);

  //populates the m_allPirates array with pirate classes from
  //the file of all the pirates
  for(int i = 0; i < MAX_PIRATES; i++){
    getline(pirates, name, ',');
    getline(pirates, rating, ',');
    getline(pirates, origin, ',');
    getline(pirates, desc);
    
    m_allPirates[i] = Pirate(name, stoi(rating), origin, desc);

  }
   cout << MAX_PIRATES << " pirates loaded." << endl;  
}

//StartGame
//randomly assigns user a pirate and ship
//manages the game 
void Game::StartGame(){
  Ship userShip;

  //randomly assigns user a pirate and a ship

  //pirate can be any pirate in the array of pirate classes
  //the number generated will be between 0 and the total
  //number of pirates in the array minus one (because indexing starts at 0)
  //(same thing for the random assignment of a ship)
  m_myPirate = m_allPirates[rand() % (MAX_PIRATES - 1) + 0];
  cout << "Congratulations! " << m_myPirate.GetName() << " is now available to plunder!" << endl;

  userShip = m_ships[rand() % (MAX_SHIPS - 1) + 0];
  m_myPirate.SetCurShip(userShip);
  cout << m_myPirate.GetName() << " is aboard a " << userShip.m_type << "." << endl;

  int option = MainMenu();
  
  //keeps calling main menu and checking to see if user wants to retire
  while(option != 4){

    if (option == 1)
      SearchTreasure();
    
    else if (option == 2)
      m_myPirate.RepairShip();
    
    else if (option == 3)
      m_myPirate.DisplayScore();
   
    option = MainMenu();
  }
  
  m_myPirate.DisplayScore();
  cout << m_myPirate.GetName() << " sails off into retirement!" << endl;
  cout << "Thanks for playing Pirates!" << endl;
}

//MainMenu
//displays and manges the menu
//returns the user's selection
int Game::MainMenu(){
  int option;
  
  cout << "What would you like to do?\n"
                "1. Search for Treasure\n"
                "2. Repair Ship\n"
                "3. See Score\n"
                "4. Retire" << endl;
  cin >> option;

  while((option < 1) && (option > 4)){
    cout << "invalid choice" << endl;
    cout << "What would you like to do?\n"
                      "1. Search for Treasure\n"
                      "2. Repair Ship\n"
                      "3. See Score\n"
                      "4. Retire" << endl;
  }
  return option;
}

//SearchTreasure
//searches for ships and allows the user to
//battle or attempt to flee
void Game::SearchTreasure(){
  int option;
  Pirate enemyPirate;
  Ship enemyShip;

  //randomly assigns the computer a pirate and ship
  enemyPirate = m_allPirates[rand() % (MAX_PIRATES - 1) + 0];
  
  enemyShip = m_ships[rand() % (MAX_SHIPS - 1) + 0];
  enemyPirate.SetCurShip(enemyShip);
  
  cout << "You scan the horizon for prospective targets..." << endl;
  cout << "Off in the distance, you see " << enemyPirate.GetName() << " on a " << enemyShip.m_type << "!" << endl;
  cout << "What would you like to do? " << endl;
  cout << "1. Attack " << enemyPirate.GetName() << endl;
  cout << "2. Attempt to Flee from " << enemyPirate.GetName() << endl;
  cin >> option;

  while (option != 1 && option != 2){
    cout << "Please select from the above options" << endl;
    cout << "What would you like to do? " << endl;
    cout << "1. Attack " << enemyPirate.GetName() << endl;
    cout << "2. Attempt to Flee from " << enemyPirate.GetName() << endl;
    cin >> option;
  }
  
  if (option == 1)
    m_myPirate.Battle(enemyPirate, enemyShip);
  
  else if (option == 2)
    m_myPirate.Flee(enemyPirate, enemyShip);  
}
