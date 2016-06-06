#pragma once

#include "Ships.h"
#include <vector>

#define SEA_POS_X 970
#define SEA_POS_Y 540

#define GRID_LENGHT 10
#define COORD_SIZE 2

enum Case_type
{
	EMPTY,
	SHIP,
	WHITE,
	RED
};

class Sea
{
public:
	Sea();

	Sea(SDL_Surface* screen, SDL_Window* window);
	
	void DrawSea(SDL_Surface * screen);

	void PlaceShip(SDL_Surface* screen, Ships* ship, int x, int y, bool rotate);
	void EraseShip(SDL_Surface* screen, Ships* ship, int xIni, int yIni, int xFinal, int yFinal, bool rotated, bool rotating);

	void CoordToArray(int coord[], int x, int y);
	void ArrayToCoord(int i, int j);

	void FillGrid(int x, int y);
	void FillGrid(Ships* ship, int x, int y, bool rotate);

	bool PositionAvailable(Ships* ship, int x, int y, bool rotate);

	//terrible Naming
	void PositionInsides(std::vector<Case_type>* caseType,int x, int y, int xFinal, int yFinal);

	~Sea();

private:
	int grid[GRID_LENGHT][GRID_LENGHT] = { EMPTY };
	int coord[COORD_SIZE];
	int coord2[COORD_SIZE];

	const char* path = "Images/BattleShips_Ships.png";

	SDL_Surface* LoadImage();

	SDL_Surface* screen;
	SDL_Surface* image;
	SDL_Rect* dstRect;
	SDL_Rect* srcRect;
};

