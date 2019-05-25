#pragma   once  
#include <iostream>
#include <random>
#include <io.h> 
#include <process.h> 
#include <vector>
#include <stdlib.h>
#include <time.h>
#include <easyx.h>
#include <conio.h>

#ifndef _variables_
#define _variables_

extern int arrayX;      	// Ocean width
extern int arrayY;       // Ocean height
extern int LIMIT;   	// Must match array bounds, expects ocean to be square
extern const char WATER;
extern const char FISH;
extern const char SHARK;

/*
extern char oceanNext[arrayX][arrayY];
extern int breed[arrayX][arrayY];
extern int breedNext[arrayX][arrayY];
extern int starve[arrayX][arrayY];
extern int starveNext[arrayX][arrayY];
extern char ocean[arrayX][arrayY];
*/

extern char** oceanNext;
extern char** ocean;
extern int** breed;
extern int** breedNext;
extern int** starve;
extern int** starveNext;


extern std::vector<int> neighbours;

extern int totalFish;
extern int allFish;    // Running count of fish
extern int totalSharks;
extern int allSharks;// Running count of sharks

extern int fishBreedTime;      // Iteration count until fish breed
extern int sharkBreedTime;     // Iteration count until sharks breed
extern int sharkStarveTime;    // Iteration count until shark dies

extern int breedLife;
extern int starveLife;

extern int randomXPos, randomYPos;

extern long int microseconds; // Timer variable
extern int drawSize;

#endif

void initDynamicArray(char** dynamicArray);
void initDynamicArray(int** dynamicArray);