#pragma once

#include <iostream>
#include "SDL.h"
#include "SDL_image.h"

#define CASE_SIZE 45
#define LINE_SIZE 5
#define CASE_LENGHT 50

#define A1_X 1015
#define A1_Y 43

#define SEA_SRC_X 0
#define SEA_SRC_Y 250
#define SEA_SIDE 555

#define GRID_X 46
#define GRID_Y 296

#define COORD_SIZE 2

enum ShipType
{
	CARRIER,
	BATTLESHIP,
	CRUISER,
	SUBMARINE,
	DESTROYER,
};

enum HitPoints
{
	DESTROYER_HP = 2,
	SUBMARINE_HP,
	CRUISER_HP = SUBMARINE_HP,
	BATTLESHIP_HP,
	CARRIER_HP
};

class Ships
{
public:
	Ships();

	Ships(ShipType shipType);

	void Draw(SDL_Surface* screen, int x, int y, bool rotate);

	//useless (Redraw sea instead)
	void Erase(SDL_Surface* screen, int xIni, int yIni, int xFinal, int yFinal, bool rotated, bool rotating);

	int GetHitPoints() const { return hitpoints; }

	~Ships();

private:

	void CoordToArray(int x, int y);
	void ArrayToCoord(int i, int j);

	const char* path = "Images/BattleShips_Ships.png";
	int coord[COORD_SIZE];

	int pos[COORD_SIZE]; 
	bool isFacingNorth;
	bool isPlaced;

	SDL_Surface* LoadImage();
	//std::vector<Case_type>* caseType;

	SDL_Surface* screen;
	SDL_Surface* image;
	SDL_Rect* dstRect;
	SDL_Rect* srcRect;
	SDL_Rect* srcRotRect;
	SDL_Rect* corRect;
	SDL_Rect* dstCorRect;

	ShipType shipType;
	HitPoints hitpoints;
};

