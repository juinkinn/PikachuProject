#pragma once
#include "Matching.h"
#include "Control.h"
#include "Interface.h"
#include<conio.h>
#include<time.h>

void initBoard(CELL**);
void renderBoard(CELL**);
void deleteBoard(CELL**);
void move(CELL**, position&, int&, player&, position [], int&);
void playGame(player&);
void displayInstruction(player&);
void clearInstruction(player&);

//source code: https://github.com/PhVanMin/Pikachuuu