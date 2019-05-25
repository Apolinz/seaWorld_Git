void populateAllArrays();
void create();
void updateOceanContents(char** toOcean, char** fromOcean,int** toBreed, int** fromBreed,int** toStarve, int** fromStarve);
void updateTotals();
int randomGen(long int range);
int getMoveDirection(char type, int xpos, int ypos);
void simulate();
void print();
void drawWater(int positionLeft, int positionTop);
void drawOcean();
void breedOrStarveToDeath();

