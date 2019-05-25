#include "stdafx.h"
#include "programSystem.h"
#include "seaLogic.h"
#include "variables.h"
#include <vector>
#include <easyx.h>
#include <time.h>

extern int totalFish;
extern int totalSharks;
extern int LIMIT;
extern int randomXPos;
extern int randomYPos;
extern int arrayX;
extern int arrayY;
extern int breedLife;
extern int starveLife;
extern int drawSize;
extern int allSharks;
extern int allFish;
extern int fishBreedTime;
extern int sharkBreedTime;
extern int sharkStarveTime;
extern std::vector<int> neighbours;
const char FISH = 'F';
const char SHARK = 'S';
const char WATER = '.';
extern char** ocean;
extern char** oceanNext;
extern int** breed;
extern int** breedNext;
extern int** starve;
extern int** starveNext;

//
void initialized() {
	initDynamicArray(oceanNext);
	initDynamicArray(ocean);
	initDynamicArray(breed);
	initDynamicArray(breedNext);
	initDynamicArray(starve);
	initDynamicArray(starveNext);
	srand(time(NULL));
	create();
	initgraph(1920, 1080);
}

void featureSwitch() {

}

void drawTheSea() {
	do {
		drawOcean();
		simulate();
		breedOrStarveToDeath();
		updateTotals();
		updateOceanContents(ocean, oceanNext, breed, breedNext, starve, starveNext);
		if (_getch() == 's') {
			cleardevice();
			printTheSea();
		}
		else{
			cleardevice();
		}
	} while (true);
}

void printTheSea() {
	do {
		print();
		simulate();
		breedOrStarveToDeath();
		updateTotals();
		updateOceanContents(ocean, oceanNext, breed, breedNext, starve, starveNext);
		if (_getch() == 's') {
			cleardevice();
			drawTheSea();
		}
		else {
			cleardevice();
		}
	} while(true);
}