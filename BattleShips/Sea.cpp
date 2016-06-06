#include "Sea.h"

Sea::Sea()
{
	image = nullptr;
	screen = nullptr;
	dstRect = nullptr;
	srcRect = nullptr;
}

Sea::Sea(SDL_Surface * screen, SDL_Window* window)
{
	image = LoadImage();

	srcRect = new SDL_Rect();
	srcRect->x = SEA_SRC_X;
	srcRect->y = SEA_SRC_Y;
	srcRect->w = SEA_SIDE;
	srcRect->h = SEA_SIDE;

	dstRect = new SDL_Rect();
	dstRect->x = SEA_POS_X;
	dstRect->y = SEA_SRC_X;
}

void Sea::DrawSea(SDL_Surface * screen)
{
	this->screen = screen;
	
	if (image != nullptr && screen != nullptr)
	{
		SDL_BlitSurface(image, srcRect, screen, dstRect);
		dstRect->y = SEA_POS_Y;
		SDL_BlitSurface(image, srcRect, screen, dstRect);
		dstRect->y = SEA_SRC_X;
	}
}

void Sea::PlaceShip(SDL_Surface * screen, Ships* ship, int x, int y, bool rotate)
{
	ship->Draw(screen, x, y, rotate);
}

void Sea::EraseShip(SDL_Surface * screen, Ships * ship, int xIni, int yIni, int xFinal, int yFinal, bool isRotated, bool isRotating)
{
	ship->Erase(screen, xIni, yIni, xFinal, yFinal, isRotated, isRotating);
}

void Sea::CoordToArray(int coord[] , int x, int y)
{
	coord[0] = (x - A1_X) / CASE_LENGHT;
	coord[1] = (y - A1_Y) / CASE_LENGHT;
}

void Sea::ArrayToCoord(int i, int j)
{
	coord[0] = A1_X + i * CASE_LENGHT;
	coord[1] = A1_Y + j * CASE_LENGHT;
}

void Sea::FillGrid(int x, int y)
{
	//MIGHT NOT WORK
	CoordToArray(coord, x, y);
	switch (grid[coord[0]][coord[1]])
	{
	case EMPTY:
		grid[coord[0]][coord[1]] = WHITE;
	case SHIP:
		grid[coord[0]][coord[1]] = RED;
	default:
		break;
	}
}

void Sea::FillGrid(Ships * ship, int x, int y, bool rotate)
{
	CoordToArray(coord, x, y);
	int hp = ship->GetHitPoints();
	if (rotate)
	{
		for (int i = coord[1]; i < coord[1] + hp; i++)
		{
			grid[coord[0]][i] = SHIP;
		}	
	}
	else
	{
		for (int i = coord[0]; i < coord[0] + hp; i++)
		{
			grid[i][coord[1]] = SHIP;
		}
	}
}

bool Sea::PositionAvailable(Ships * ship, int x, int y, bool rotate)
{
	CoordToArray(coord, x, y);
	int hp = ship->GetHitPoints();
	if (rotate)
	{
		for (int i = coord[1]; i < coord[1] + hp; i++)
		{
			if ((coord[1] + hp) > 10)
				return false;
			if (grid[coord[0]][i] == SHIP)
				return false;
		}
	}
	else
	{
		for (int i = coord[0]; i < coord[0] + hp; i++)
		{
			if ((coord[0] + hp) > 10)
				return false;
			if (grid[i][coord[1]] == SHIP)
				return false;
		}
	}

	return true;
}

void Sea::PositionInsides(std::vector<Case_type>* caseType, int xIni, int yIni, int xFinal, int yFinal)
{
	CoordToArray(coord, xIni, yIni);
	CoordToArray(coord2, xFinal, yFinal);

	for (int i = coord[0]; i < coord2[0]; i++)
	{
		//caseType->insert(grid[i][coord[1]]);
	}
}

Sea::~Sea()
{
	delete dstRect;
	delete srcRect;
	SDL_FreeSurface(image);
}

SDL_Surface * Sea::LoadImage()
{
	SDL_Surface* image = IMG_Load(path);
	if (image == nullptr)
	{
		printf("Unable to load image at path: %s, SDL_Error: %s\n", path, SDL_GetError());
	}
	return image;
}

