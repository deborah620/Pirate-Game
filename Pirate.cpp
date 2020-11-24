//Title: Pirate.cpp
//Author: Deborah Miller
//Date: 9/24/2020
//Section: 10/14
//Email: d169@umbc.edu
//Description: This is part of the Pirate Project in CMSC 202 @ UMBC
// it is the .cpp file for the pirate .h file

#include "Ship.h"
#include "Pirate.h"

const int CALC_TREASURE = 3; //number used in calculating treasure received
const int MIN = 1; //used for rand() parameters
const int MAX = 100; //used for rand() parameters

//Pirate
//default constructor
Pirate::Pirate(){
  m_pirateName = "Uluj Ali";
  SetRating(72);
  m_pirateOrigin = "Turkey";
  m_pirateDesc = "An Italian-born Muslim corsair\
                  who later became an Ottoman admiral\
                  and Chief Admiral of the Ottoman Fleet\
                  in the 16th century.";
}

//Pirate
//overloaded contstructor
Pirate::Pirate(string name, int rating, string origin, string desc){
  m_pirateName = name;
  SetRating(rating);
  m_pirateOrigin = origin;
  m_pirateDesc = desc;
}

//GetName
//returns the pirate's name
string Pirate::GetName(){
  return m_pirateName;
}

//GetRating
//returns the pirate's rating
int Pirate::GetRating(){
  return m_pirateRating;
}

//SetRating
//sets the pirate's rating
void Pirate::SetRating(int rating){
  m_pirateRating = rating;
}

//GetOrigin
//returns the pirate's origin
string Pirate::GetOrigin(){
  return m_pirateOrigin;
}

//GetDesc
//returns the pirate's description
string Pirate::GetDesc(){
  return m_pirateDesc;
}

//SetCurShip
//sets the pirate's ship 
void Pirate::SetCurShip(Ship curShip){
  m_curShip = curShip;
}

//CalcTreasure
//updates the pirates cargo when he wins a battle
//(adds the enemy's cannon, max toughness and speed divided by 3)
void Pirate::CalcTreasure(Ship enemyShip){
  m_pirateCargo = m_pirateCargo + ((enemyShip.m_cannon + enemyShip.m_toughness + enemyShip.m_speed) / CALC_TREASURE);
}

//Battle
//battles user's pirate and computer's pirate,
//they take turns shooting cannons at eachother
//until one of their toughness's is less than one
//then the appropriate action is performed depending on who won
void Pirate::Battle(Pirate enemyPirate, Ship enemyShip){
  int userShotHit = 0;
  int enemyShotHit = 0;
  int randomNum;
  bool enemyShipDestroyed = false;
  bool userShipDestroyed = false;
  
  if(m_curShip.m_curToughness < 1)
    cout << "You must first repair your ship" << endl;

  else{
    m_pirateDays += 1;
    cout << "A naval battle of the ages commences between " << m_pirateName << " and " << enemyPirate.m_pirateName << endl;

    while(!enemyShipDestroyed && !userShipDestroyed) {
      //user's pirate's turn
      cout << m_pirateName << " fires " << m_curShip.m_cannon << " cannons!" << endl;

      //since the pirate has a their rating out of 100 chance of hitting an enemy ship
      //this loop finds a random number between 1 and 100 and if it falls in the range of
      //1 to the user's pirate rating, a cannon hits the enemy ship
      //it goes through this loop for as many cannons as the ship has to fire
      for(int i = 0; i < m_curShip.m_cannon; i++){
	randomNum = rand() % (MAX + MIN);
	
	if (randomNum <= m_pirateRating){
	  userShotHit ++;	  
	}

      }
    
      //minuses the appropriate amount from current toughness if the ship is shot
      enemyShip.m_curToughness = enemyShip.m_curToughness - userShotHit;
      cout << userShotHit << " shots hit!" << endl;
      userShotHit = 0;

      //if the enemy ship's current toughness is less then one, the loop stops
      if (enemyShip.m_curToughness < 1)
	enemyShipDestroyed = true;

      else{
	//enemy's pirate's turn
	cout << enemyPirate.m_pirateName << " fires " << enemyShip.m_cannon << " back!" << endl;;

	for(int i = 0; i < enemyShip.m_cannon; i++){
	  randomNum = rand() % (MAX + MIN);

	  if (randomNum <= enemyPirate.m_pirateRating){
	    enemyShotHit ++;
	  }
	  cout << "rand num: " << randomNum << endl;
	}
	
	m_curShip.m_curToughness = m_curShip.m_curToughness - enemyShotHit;
	cout << enemyShotHit << " shots hit!" << endl;
	enemyShotHit = 0;
	if(m_curShip.m_curToughness < 1)
	  userShipDestroyed = true;
      }
    }
  
    if(enemyShip.m_curToughness < 1) {
      cout << "You win!" << endl;
      cout << m_pirateName << " shares " <<  ((enemyShip.m_cannon + enemyShip.m_toughness + enemyShip.m_speed) / CALC_TREASURE)
	   << " treasure with their crew!" << endl;
      //updates user's treasure
      CalcTreasure(enemyShip);
      
    }
    else if(m_curShip.m_curToughness < 1){
      cout << "You lose!" << endl;
      m_curShip.m_curToughness = 0;
      m_pirateCargo = m_pirateCargo/2;
    }
  }
}

//RepairShip
//repairs the user's ship to it's max toughness if needed
void Pirate::RepairShip(){
  int days = 0;
  
  if(m_curShip.m_curToughness == m_curShip.m_toughness)
    cout << "Your ship doesn't need repairs" << endl;

  else{
    days = (m_curShip.m_toughness - m_curShip.m_curToughness);
    m_pirateDays += days;
    cout << "It takes " << days << " days to repair your " << m_curShip.m_type << endl;
    m_curShip.m_curToughness = m_curShip.m_toughness;
  }

}

//Flee
//if the user's ship is faster than the computer's ship, it flees
//if not it's drawn into battlie
void Pirate::Flee(Pirate enemyPirate, Ship enemyShip){
  m_pirateDays += 1;

  cout << "You attempt to flee from " << enemyPirate.m_pirateName << endl;

  if (m_curShip.m_speed > enemyShip.m_speed){
    cout << "You narrowly escape from " << enemyPirate.m_pirateName << endl;
  }

  else{
    cout << enemyPirate.m_pirateName << " catches up to you, and draws you into battle!" << endl;
    Battle(enemyPirate, enemyShip);
  }
  
}

//DisplayScore
//displays the user's information
void Pirate::DisplayScore(){
  
  cout << "**********************" << endl;
  cout << "Name: " << m_pirateName << endl;
  cout << "Rating: " << m_pirateRating << endl;
  cout << "Country of Origin: " << m_pirateOrigin << endl;
  cout << "Description: " << m_pirateDesc << endl;
  cout << "Days Sailing: " << m_pirateDays << endl;
  cout << "Cargo Captured: " << m_pirateCargo << endl;

  if (m_pirateDays == 0)
    cout << "Cargo Per Day: " << m_pirateDays << endl;
  else
    cout << "Cargo Per Day: " << (double(m_pirateCargo)/m_pirateDays) << endl;

  cout << "Ship Type: " << m_curShip.m_type << endl;
  cout << "Ship Cannons: " << m_curShip.m_cannon << endl;
  cout << "Ship Current Toughness: " << m_curShip.m_curToughness << endl;
  cout << "Ship Max Toughness: " << m_curShip.m_toughness << endl;
  cout << "Ship Speed: " << m_curShip.m_speed << endl;
  cout << "*********************" << endl;
}

