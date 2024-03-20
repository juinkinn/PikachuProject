#pragma once
#include<fstream>
#include<string>
#include "Control.h"
#include "Struct.h"
using namespace std;

void readLeaderBoard();
void writeLeaderBoard(player);
void getPlayerInfo(player&);
void displayStatus(bool);
void getBackground(char [][41]);
void displayBackground(char [][41], int, int);
int mainMenu();

//source code: https://github.com/PhVanMin/Pikachuuu