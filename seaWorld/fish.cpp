#include "stdafx.h"
#include <easyx.h>

extern int totalFish;
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

void populateWithFish() {
	for (int i = 0; i < totalFish; ++i) {
		randomXPos = (int)rand() % LIMIT;
		randomYPos = (int)rand() % LIMIT;
		ocean[randomXPos][randomYPos] = FISH;
		breed[randomXPos][randomYPos] = breedLife;
		starve[randomXPos][randomXPos] = starveLife;
	}
}

void deleteFish(int xpos, int ypos) {
	ocean[xpos][ypos] = SHARK;
	starve[xpos][ypos] = 0;
	breed[xpos][ypos] = 0;
}

void drawFish(int positionLeft, int positionTop) {
	int positionRight = positionLeft + drawSize;
	int positionBottom = positionTop + drawSize;
	setfillcolor(GREEN);
	fillrectangle(positionLeft, positionTop, positionRight, positionBottom);
}

