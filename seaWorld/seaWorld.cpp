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

int main() {
	setUpGUI();
	initialized();
	drawTheSea();
}