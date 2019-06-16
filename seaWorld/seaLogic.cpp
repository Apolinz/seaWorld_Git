#include "stdafx.h"
#include "fish.h"
#include "shark.h"
#include <easyx.h>
#include <vector>
#include<iostream>

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

//Initalized the start-up array for the simulate
void populateAllArrays() {
	for (int i = 0; i <= LIMIT; ++i) {
		for (int k = 0; k <= LIMIT; ++k) {
			ocean[i][k] = WATER;
			oceanNext[i][k] = WATER;
			breed[i][k] = 0;
			breedNext[i][k] = 0;
			starve[i][k] = 0;
			starveNext[i][k] = 0;
		}
	}
}

//Generate a random number in the Interval [0,range]
int randomGen(long int range) {
	return rand() % range;
}

void updateOceanContents(char** toOcean, char** fromOcean,
	int** toBreed, int** fromBreed,
	int** toStarve, int** fromStarve) {
	for (int i = 0; i <= LIMIT; ++i) {
		for (int k = 0; k <= LIMIT; ++k) {
			toOcean[i][k] = fromOcean[i][k];
			toBreed[i][k] = fromBreed[i][k];
			toStarve[i][k] = fromStarve[i][k];

			fromOcean[i][k] = WATER;
			fromBreed[i][k] = 0;
			fromStarve[i][k] = 0;
		}
	}
}

//Count the number of the fishs and sharks in the sea
void updateTotals() {
	allSharks = 0;
	allFish = 0;
	for (int i = 0; i <= LIMIT; ++i) {
		for (int k = 0; k < LIMIT; ++k) {
			if (ocean[i][k] == FISH) {
				++allFish;
			}
			if (ocean[i][k] == SHARK) {
				++allSharks;
			}
		}
	}
}

//Popular the whole sea system
void create() {
	populateAllArrays();
	populateWithFish();
	populateWithSharks();
}

//Choose the random direction that the fish and sharks to move
int getMoveDirection(char type, int xpos, int ypos) {
	neighbours.clear();
	if (xpos == 0) {
		xpos++;
	}
	if (ypos == 0) {
		ypos++;
	}
	if (type == SHARK) {
		if (ocean[xpos - 1][ypos] == FISH) {
			neighbours.push_back(1);
			breed[xpos][ypos]++; //found a fish increment breed time
		}
		else if (ocean[xpos + 1][ypos] == FISH) {
			neighbours.push_back(2);
			breed[xpos][ypos]++; //found a fish increment breed time
		}
		else if (ocean[xpos][ypos + 1] == FISH) {
			neighbours.push_back(3);
			breed[xpos][ypos]++; //found a fish increment breed time
		}
		else if (ocean[xpos][ypos - 1] == FISH) {
			neighbours.push_back(4);
			breed[xpos][ypos]++; //found a fish increment breed time
		}
	}
	if ((type == FISH) || ((type == SHARK) && (neighbours.size() == 0))) {
		if (type == SHARK) {
			starve[xpos][ypos]++;
		} // No neighbouring fish - decide the fish die or not die
		if (ocean[xpos - 1][ypos] == WATER) {
			neighbours.push_back(1);
		}
		if (ocean[xpos + 1][ypos] == WATER) {
			neighbours.push_back(2);
		}
		if (ocean[xpos][ypos + 1] == WATER) {
			neighbours.push_back(3);
		}
		if (ocean[xpos][ypos - 1] == WATER) {
			neighbours.push_back(4);
		}
	}
	if (neighbours.size() == 0) {
		return 0;
	}
	else {
		if (type == FISH) {
			breed[xpos][ypos]++;
		} //Fish can move increment breed time
		int direction = randomGen(int(neighbours.size()));

		return neighbours[direction];
	}
}

void simulate() {
	for (int i = 0; i < LIMIT; ++i) {
		for (int k = 0; k < LIMIT; ++k) {
			if ((ocean[i][k] == FISH) || (ocean[i][k] == SHARK)) {
				int direction = getMoveDirection(ocean[i][k], i, k);
				if (direction == 0) { // Can't move
					if (ocean[i][k] == FISH) {
						oceanNext[i][k] = FISH;
					}
					if (ocean[i][k] == SHARK) {
						oceanNext[i][k] = SHARK;
					}
					breedNext[i][k] = breed[i][k];
					starveNext[i][k] = starve[i][k];
				}
				else if (direction == 1) { // North
					if (ocean[i][k] == FISH) {
						oceanNext[(i + LIMIT - 1) % LIMIT][k] = FISH;
					}
					if (ocean[i][k] == SHARK) {
						oceanNext[(i + LIMIT - 1) % LIMIT][k] = SHARK;
					}
					starveNext[(i + LIMIT - 1) % LIMIT][k] = starve[i][k];
					breedNext[(i + LIMIT - 1) % LIMIT][k] = breed[i][k];
				}
				else if (direction == 2) { // South
					if (ocean[i][k] == FISH) {
						oceanNext[(i + 1) % LIMIT][k] = FISH;
					}
					if (ocean[i][k] == SHARK) {
						oceanNext[(i + 1) % LIMIT][k] = SHARK;
					}
					starveNext[(i + 1) % LIMIT][k] = starve[i][k];
					breedNext[(i + 1) % LIMIT][k] = breed[i][k];
				}
				else if (direction == 3) { // East
					if (ocean[i][k] == FISH) {
						oceanNext[i][(k + 1) % LIMIT] = FISH;
					}
					if (ocean[i][k] == SHARK) {
						oceanNext[i][(k + 1) % LIMIT] = SHARK;
					}
					starveNext[i][(k + 1) % LIMIT] = starve[i][k];
					breedNext[i][(k + 1) % LIMIT] = breed[i][k];
				}
				else if (direction == 4) { // West
					if (ocean[i][k] == FISH) {
						oceanNext[i][(k + LIMIT - 1) % LIMIT] = FISH;
					}
					if (ocean[i][k] == SHARK) {
						oceanNext[i][(k + LIMIT - 1) % LIMIT] = SHARK;
					}
					starveNext[i][(k + LIMIT - 1) % LIMIT] = starve[i][k];
					breedNext[i][(k + LIMIT - 1) % LIMIT] = breed[i][k];
				}
			}
		}
	}
}

//The function the decide whether the creatures breed or died
void breedOrStarveToDeath() {
	for (int xPosition = 0; xPosition <= LIMIT; xPosition++) {
		for (int yPosition = 0; yPosition <= LIMIT;yPosition++) {
			if (totalFish >= 2 && ocean[xPosition][yPosition] == FISH) {
				if (breed[xPosition][yPosition] >= fishBreedTime) {
					if (ocean[(xPosition + 1) % arrayX][yPosition] == WATER) {
						oceanNext[(xPosition + 1) % arrayX][yPosition] = FISH;
					}
					else if(ocean[(xPosition + arrayX - 1) % arrayX][yPosition] == WATER){
						oceanNext[(xPosition + arrayX - 1) % arrayX][yPosition] = FISH;
					}
					else if(ocean[xPosition][(yPosition + 1) % arrayY] == WATER) {
						oceanNext[xPosition][(yPosition + 1) % arrayY] = FISH;
					}
					else if (ocean[xPosition][(yPosition + arrayY - 1) % arrayY] == WATER) {
						oceanNext[xPosition][(yPosition + arrayY - 1) % arrayY] = FISH;
					}
				}
			}			
			if (totalSharks >= 2 && ocean[xPosition][yPosition] == SHARK) {
				if (breed[xPosition][yPosition] >= sharkBreedTime) {
					if (ocean[(xPosition + 1) % arrayX][yPosition] == WATER) {
						oceanNext[(xPosition + 1) % arrayX][yPosition] = SHARK;
					}
					else if (ocean[(xPosition + arrayX - 1) % arrayX][yPosition] == WATER) {
						oceanNext[(xPosition + arrayX - 1) % arrayX][yPosition] = SHARK;
					}
					else if (ocean[xPosition][(yPosition + 1) % arrayY] == WATER) {
						oceanNext[xPosition][(yPosition + 1) % arrayY] = SHARK;
					}
					else if (ocean[xPosition][(yPosition + arrayY - 1) % arrayY] == WATER) {
						oceanNext[xPosition][(yPosition + arrayY - 1) % arrayY] = SHARK;
					}
				}
			}
			if (starveNext[xPosition][yPosition] == sharkStarveTime) {
				oceanNext[xPosition][yPosition] = WATER;
			}
		}
	}
}

//***********************Draw-Related functions***************************
void print() {
	int xPosition = 0;
	int yPosition = 0;
	char fishString[] = "Fish[";
	char sharkString[] = "]Shark[";
	char endString[] = "]";
	char sharkNum = totalSharks;
	char fishNum = totalFish;
	for (int i = 0; i < LIMIT; ++i) {
		//outtextxy(xPosition, yPosition, ' ');
		for (int k = 0; k < LIMIT; ++k) {
			//std::cout << ocean[i][k];
			outtextxy(xPosition, yPosition, ocean[i][k]);
			xPosition += 25;
		}
		//std::cout << std::endl;
		xPosition = 0;
		yPosition += 25;
	}

	//A TO-DO method to print the total number of the shark and fishs
	/*
	//the text print function
	for (int printUnderLine = 0; printUnderLine <= 25; printUnderLine++) {
		outtextxy(xPosition, yPosition, '_');
		xPosition += 10;
	}
	xPosition = 0;
	yPosition += 25;
	for (int count = 0; count <= 5; count++) {
		outtextxy(xPosition, yPosition, fishString[count]);
		xPosition += 8;
	}
	for (int count = 0; count <= 7; count++) {
		outtextxy(xPosition, yPosition, sharkString[count]);
		xPosition += 8;
	}
	outtextxy(xPosition,yPosition,*endString);
	*/
}

void drawWater(int positionLeft, int positionTop) {
	int positionRight = positionLeft + drawSize;
	int positionBottom = positionTop + drawSize;
	setfillcolor(BLUE);
	fillrectangle(positionLeft, positionTop, positionRight, positionBottom);
}

void drawOcean() {
	int drawPositionX = 0;
	int	drawPositionY = 0;
	BeginBatchDraw();
	for (int i = 0; i < LIMIT; ++i) {
		for (int k = 0; k < LIMIT; ++k) {
			if (ocean[i][k] == WATER) {
				drawWater(drawPositionX, drawPositionY);
			}
			else if (ocean[i][k] == SHARK) {
				drawShark(drawPositionX, drawPositionY);
			}
			else if (ocean[i][k] == FISH) {
				drawFish(drawPositionX, drawPositionY);
			}
			drawPositionX += drawSize;
			//Sleep(10);
		}
		drawPositionX = 0;
		drawPositionY += drawSize;
	}
	FlushBatchDraw();
}

