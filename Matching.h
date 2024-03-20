#pragma once
#include "Struct.h"

bool checkNext(CELL**, int p1, int p2, int q1, int q2);
bool checkLine(CELL**, int p1, int p2, int q1, int q2);
bool checkImatching(CELL**, int p1, int p2, int q1, int q2);
bool checkLmatching(CELL**, int p1, int p2, int q1, int q2);
bool checkZmatching(CELL**, int p1, int p2, int q1, int q2);
bool checkUmatching(CELL**, int p1, int p2, int q1, int q2);
bool checkAll(CELL**, int p1, int p2, int q1, int q2);
bool checkValidPairs(CELL**);

//source code: https://github.com/PhVanMin/Pikachuuu