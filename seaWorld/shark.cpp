#include "stdafx.h"
#include <easyx.h>

extern int totalSharks;
extern int LIMIT;
extern int randomXPos;
extern int randomYPos;
extern int breedLife;
extern int starveLife;
extern int drawSize;
const char FISH = 'F';
const char SHARK = 'S';
const char WATER = '.';
extern char** ocean;
extern int** breed;
extern int** starve;

void populateWithSharks() {
	ocean[0][0] = SHARK;
	for (int i = 0; i < totalSharks; ++i) {
		randomXPos = (int)rand() % LIMIT;
		randomYPos = (int)rand() % LIMIT;
		ocean[randomXPos][randomYPos] = SHARK;
		breed[randomXPos][randomYPos] = breedLife;
		starve[randomXPos][randomYPos] = starveLife;
	}
}

void deleteShark(int xpos, int ypos) {
	ocean[xpos][ypos] = WATER;
	starve[xpos][ypos] = 0;
	breed[xpos][ypos] = 0;
}

void drawShark(int positionLeft, int positionTop) {
	int positionRight = positionLeft + drawSize;
	int positionBottom = positionTop + drawSize;
	setfillcolor(RED);
	fillrectangle(positionLeft, positionTop, positionRight, positionBottom);
}