#include "stdafx.h"
#include "programSystem.h"
#include "seaLogic.h"
#include "variables.h"
#include <iostream>
#include <stdio.h>
#include <conio.h>
#include <graphics.h>
#include <vector>
#include <easyx.h>
#include <time.h>
#include <typeinfo>
#include <conio.h>
#include <TCHAR.h>


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

/*
void setUpGUI() {
	char defaultChar[10];
	char jungle[10] = "d";
	std::cout << "input the width of the sea(input 'd' to pass):";
	std::cin >> defaultChar;
	if (strcmp(defaultChar,jungle) == 0) {
		LIMIT = 10;
	}
	else {
		sscanf_s(defaultChar, "%d", &LIMIT);
		if (LIMIT <= 0) {
			LIMIT = 10;
		}
	}
	arrayX = LIMIT;
	arrayY = LIMIT;

	std::cout << "input the number of the shark(input 'd' to pass):";
	std::cin >> defaultChar;
	if (strcmp(defaultChar, jungle) == 0) {
		allSharks = 10;
	}
	else {
		sscanf_s(defaultChar, "%d", &allSharks);
	}

	std::cout << "input the number of the fish(input 'd' to pass):";
	std::cin >> defaultChar;
	if (strcmp(defaultChar, jungle) == 0) {
		allFish = 10;
	}
	else {
		sscanf_s(defaultChar, "%d", &allFish);
	}
}
*/

void setUpGUI() {
	char inputNum[10];
	initgraph(600, 400);
	InputBox(inputNum, 10, _T("please input the width of the sea"));
	sscanf_s(inputNum, "%d", &LIMIT);
	InputBox(inputNum, 10, _T("please input the number of the shark"));
	sscanf_s(inputNum, "%d", &totalSharks);
	InputBox(inputNum, 10, _T("please input the number of the fish"));
	sscanf_s(inputNum, "%d", &totalFish);

}

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