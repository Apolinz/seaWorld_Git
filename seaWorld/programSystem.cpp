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
static int waterNum = 0;
static int fishNum = 0;
static int sharkNum = 0;


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
	initgraph(1000, 1000);
	InputBox(inputNum, 10, _T("please input the width of the sea"));
	sscanf_s(inputNum, "%d", &LIMIT);
	arrayX = LIMIT;
	arrayY = LIMIT;
	InputBox(inputNum, 10, _T("please input the number of the shark"));
	sscanf_s(inputNum, "%d", &totalSharks);
	InputBox(inputNum, 10, _T("please input the number of the fish"));
	sscanf_s(inputNum, "%d", &totalFish);
	closegraph();
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

/*void transformDataToCode() {
	int checkFlag = 0;//checkFlag Water:0 Fish:1 Shark:2
	int printX = 0;
	int printY = 0;
	int gapSize = 18;
	char textToPrint[5];
	char endlLine[] = "/n";
	char splitData[] = "|";
	do {
		for (int countWidth = 0; countWidth < LIMIT; countWidth++) {
			for (int countHeight = 0; countHeight < LIMIT; countHeight++) {
				if (oceanNext[countWidth][countHeight] = WATER) {
					if (checkFlag != 0) {
						checkFlag = 0;
						if (checkFlag = 1) {
							//outtextxy(printX, printY, "F");
							//printX += gapSize;
							outtext(FISH);
							sprintf_s(textToPrint, "%d", fishNum);
							outtext(textToPrint);
							outtext(splitData);
							//printX += gapSize;
							//outtextxy(printX, printY, "|");
							outtext('/n');
							//printX += gapSize;
							fishNum = 0;
						}
						if (checkFlag = 2) {
							//outtextxy(printX, printY, "S");
							//printX += gapSize;
							outtext(SHARK);
							sprintf_s(textToPrint, "%d", sharkNum);
							outtext(textToPrint);
							outtext(splitData);
							//printX += gapSize;
							//outtextxy(printX, printY, "|");
							outtext(endlLine);
							//printX += gapSize;
							sharkNum = 0;
						}
					}
					waterNum++;
				}
				if (oceanNext[countWidth][countHeight] = FISH) {
					if (checkFlag != 1) {
						checkFlag = 1;
						if (checkFlag = 0) {
							//outtextxy(printX, printY, ".");
							//printX += gapSize;
							outtext(WATER);
							sprintf_s(textToPrint, "%d", waterNum);
							outtext(textToPrint);
							outtext(splitData);
							//printX += gapSize;
							//outtextxy(printX, printY, "|");
							outtext(endlLine);
							//printX += gapSize;
							waterNum = 0;
						}
						if (checkFlag = 2) {
							//outtextxy(printX, printY, "S");
							outtext(SHARK);
							//printX += gapSize;
							sprintf_s(textToPrint, "%d", sharkNum);
							outtext(textToPrint);
							outtext(splitData);
							//printX += gapSize;
							//outtextxy(printX, printY, "|");
							outtext(endlLine);
							//printX += gapSize;
							sharkNum = 0;
						}
					}
					fishNum++;
				}
				if (oceanNext[countWidth][countHeight] = SHARK) {
					if (checkFlag != 2) {
						checkFlag = 0;
						if (checkFlag = 0) {
							//outtextxy(printX, printY, ".");
							outtext(WATER);
							//printX += gapSize;
							sprintf_s(textToPrint, "%d", waterNum);
							outtext(textToPrint);
							outtext(splitData);
							//printX += gapSize;
							//outtextxy(printX, printY, "|");
							outtext(endlLine);
							//printX += gapSize;
							waterNum = 0;
						}
						if (checkFlag = 1) {
							//outtextxy(printX, printY, "F");
							outtext(FISH);
							//printX += gapSize;
							sprintf_s(textToPrint, "%d", fishNum);
							outtext(textToPrint);
							outtext(splitData);
							//printX += gapSize;
							outtext(endlLine);
							//outtextxy(printX, printY, "|");
							//printX += gapSize;
							fishNum = 0;
						}
					}
					sharkNum++;
				}
				//printX += gapSize;
			}
			//printX = 0;
			//printY += gapSize;
		}
		//printX = 0;
		//printY = 0;
		if (_getch() == 's') {
			cleardevice();
			drawTheSea();
		}
		else {
			cleardevice();
		}
	}while(true);
}*/


