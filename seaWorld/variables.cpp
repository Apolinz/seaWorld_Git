#include "stdafx.h"
#include <iostream>
#include <random>
#include <io.h> 
#include <process.h> 
#include <vector>
#include <stdlib.h>
#include <time.h>
#include <easyx.h>
#include <conio.h>

int arrayX = 80;      	// Ocean width
int arrayY = 80;       // Ocean height
int LIMIT = 80;   	// Must match array bounds, expects ocean to be square
const char WATER = '.';
const char FISH = 'F';
const char SHARK = 'S';

char** oceanNext = new char* [arrayX];
char** ocean = new char* [arrayX];
int** breed = new int* [arrayX];
int** breedNext = new int* [arrayX];
int** starve = new int* [arrayX];
int** starveNext = new int* [arrayX];


std::vector<int> neighbours;

int totalFish = 5;
int allFish = totalFish;    // Running count of fish
int totalSharks = 70;
int allSharks = totalSharks;// Running count of sharks

int fishBreedTime = 5;      // Iteration count until fish breed
int sharkBreedTime = 5;     // Iteration count until sharks breed
int sharkStarveTime = 10;    // Iteration count until shark dies

int breedLife = 5;
int starveLife = 3;

int randomXPos, randomYPos = 0;

long int microseconds = 1000000; // Timer variable
int drawSize = 10;

//initilize the array dynamicly
void initDynamicArray(char** dynamicArray) {
	for (int arrayWidth = 0; arrayWidth <= LIMIT; arrayWidth++) {
		dynamicArray[arrayWidth] = new char[LIMIT];
	}
}

void initDynamicArray(int** dynamicArray) {
	for (int arrayWidth = 0; arrayWidth <= LIMIT; arrayWidth++) {
		dynamicArray[arrayWidth] = new int[LIMIT];
	}
}
