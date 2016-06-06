#pragma once
#include <vector>

#include "Sea.h"

//Only playable in 1920 per 1080
#define SCREEN_WIDTH 1920
#define SCREEN_HEIGHT 1080

#define TITLE "BattleShips"

class BattleShips
{
public:
	BattleShips();

	void PlaceShip(SDL_Surface* screen, Sea* sea, SDL_Window* window, Ships* ship);

	~BattleShips();
private:
	SDL_Window* window;
	SDL_Surface* screen;
	Ships* carrier;
	Ships* battheship;
	Ships* cruiser;
	Ships* submarine;
	Ships* destroyer;
	Sea* seaPlayer1;
	Sea* seaPlayer2;

	std::vector<Ships*> fleet;
};

