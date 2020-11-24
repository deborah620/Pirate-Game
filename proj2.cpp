//Title: Project 2 for Fall 2020
//Author: Deborah Miller
//Section: 10/14
//Email: d169@umbc.edu
//Date: 9/24/2020
//Description: This is main for project 2

#include "Game.h"

#include <iostream>
#include <cstdlib>
#include <string>
#include <ctime>
using namespace std;

int main () {
  srand(time(NULL));
  Game newGame;
  newGame.StartGame();
  return 0;
}
