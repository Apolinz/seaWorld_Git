#include "stdafx.h"
#include "fish.h"
#include "seaLogic.h"
#include "shark.h"
#include "variables.h"
#include "programSystem.h"
#include <iostream>
#include <random>
#include <io.h> 
#include <process.h> 
#include <vector>
#include <stdlib.h>
#include <time.h>
#include <easyx.h>
#include <conio.h>




/*
int main(){
	//Initialize the structure of the sea
	initDynamicArray(oceanNext);
	initDynamicArray(ocean);
	initDynamicArray(breed);
	initDynamicArray(breedNext);
	initDynamicArray(starve);
	initDynamicArray(starveNext);
	//generate the time as the random number seed
	srand(time(NULL));
	//std::cout << "Wator World Simulation" << std::endl;
	create();

	//the initialize of the draw moudle
	initgraph(1920, 1080);
	do {
		drawOcean();
		simulate();
		breedOrStarveToDeath();
		updateTotals();
		updateOceanContents(ocean, oceanNext, breed, breedNext, starve, starveNext);
		_getch();
		cleardevice();
	} while (true);

	//the deafult print function
	do{
		print();
		simulate();
		breedOrStarveToDeath();
		updateTotals();
		updateOceanContents(ocean, oceanNext, breed, breedNext, starve, starveNext);
		_getch();
		cleardevice();
	} while ((allSharks > 0) && (allFish > 0));

	return 0;
}
*/

int main() {
	initialized();
	drawTheSea();
}
