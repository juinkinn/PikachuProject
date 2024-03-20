#pragma once
#include<string>
using namespace std;

#define BOARDWIDTH 8
#define BOARDHEIGHT 5

#define KEY_UP 72
#define KEY_DOWN 80
#define KEY_LEFT 75
#define KEY_RIGHT 77
#define ESC_KEY 27
#define ENTER_KEY 13

struct position {
	int x, y;
};

struct player {
	string name = "";
	int point, life;
};

struct CELL {
	int i, j;
	char c = ' ';
	bool isValid = 1, isSelected = 0;
	void drawBox(int);
	void deleteBox();
};

//source code: https://github.com/PhVanMin/Pikachuuu