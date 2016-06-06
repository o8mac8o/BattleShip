#include "Ships.h"

Ships::Ships()
{
	image = nullptr;
	screen = nullptr;
	dstRect = nullptr;
	srcRect = nullptr;
}

Ships::Ships(ShipType shipType)
	:shipType(shipType)
{
	image = LoadImage();
	dstRect = nullptr;

	//Could be changed
	switch (shipType)
	{
	case CARRIER:
		hitpoints = CARRIER_HP;
		break;
	case BATTLESHIP:
		hitpoints = BATTLESHIP_HP;
		break;
	case CRUISER:
		hitpoints = CRUISER_HP;
		break;
	case SUBMARINE:
		hitpoints = SUBMARINE_HP;
		break;
	case DESTROYER:
		hitpoints = DESTROYER_HP;
		break;
	default:
		break;
	}

	srcRect = new SDL_Rect();
	srcRect->x = NULL;
	srcRect->y = shipType * (CASE_SIZE + LINE_SIZE);
	srcRect->w = (hitpoints * CASE_SIZE) + ((hitpoints - 1) * LINE_SIZE);
	srcRect->h = CASE_SIZE;

	srcRotRect = new SDL_Rect();
	srcRotRect->x = SEA_SRC_Y + shipType * CASE_LENGHT;
	srcRotRect->y = NULL;
	srcRotRect->w = CASE_SIZE;
	srcRotRect->h = (hitpoints * CASE_SIZE) + ((hitpoints - 1) * LINE_SIZE);
}

void Ships::Draw(SDL_Surface* screen, int x, int y, bool rotate)
{
	this->screen = screen;

	dstRect = new SDL_Rect();
	dstRect->x = x;
	dstRect->y = y;

	if (image != nullptr && screen != nullptr)
	{
		if (rotate)
		{
			SDL_BlitSurface(image, srcRotRect, screen, dstRect);
		}
		else
		{
			SDL_BlitSurface(image, srcRect, screen, dstRect);
		}
	}
}

void Ships::Erase(SDL_Surface* screen, int xIni, int yIni, int xFinal, int yFinal, bool isRotated, bool isRotating)
{
	this->screen = screen;

	corRect = new SDL_Rect();
	
	dstCorRect = new SDL_Rect();
	dstCorRect->x = xIni;
	dstCorRect->y = yIni;
	if (isRotating)
	{
		if (image != nullptr && screen != nullptr)
		{
			if (isRotated)
			{
				//for (int i = ; i < xIni + hitpoints; i++)
				//{
				//
				//}


				corRect->x = GRID_X;
				corRect->y = GRID_Y;
				corRect->w = CASE_SIZE;
				corRect->h = (hitpoints * CASE_SIZE) + ((hitpoints - 1) * LINE_SIZE);
				SDL_BlitSurface(image, corRect, screen, dstCorRect);
			}
			else
			{
				corRect->x = GRID_X;
				corRect->y = GRID_Y;
				corRect->h = CASE_SIZE;
				corRect->w = (hitpoints * CASE_SIZE) + ((hitpoints - 1) * LINE_SIZE);
				SDL_BlitSurface(image, corRect, screen, dstCorRect);
			}
		}
	}
	else
	{
		if (image != nullptr && screen != nullptr)
		{
			if (isRotated)
			{
				//CORRECT 1rst case with image, copy rest with screen
				corRect->x = xFinal;
				corRect->y = yFinal;
				corRect->w = CASE_SIZE;
				corRect->h = (hitpoints * CASE_SIZE) + ((hitpoints - 1) * LINE_SIZE);
				//SDL_BlitSurface(image, corRect, screen, dstCorRect);
				SDL_BlitSurface(screen, corRect, screen, dstCorRect);
			}
			else
			{
				if (xIni > xFinal)
				{
					dstCorRect->x = xIni + (hitpoints - 1) * CASE_LENGHT;
					dstCorRect->y = yIni;
					corRect->x = xIni - CASE_LENGHT;
					corRect->y = yIni;
					corRect->w = CASE_LENGHT;
					corRect->h = CASE_LENGHT;
					SDL_BlitSurface(screen, corRect, screen, dstCorRect);
				}
				else if (xIni < xFinal)
				{
					dstCorRect->x = xIni;
					dstCorRect->y = yIni;
					corRect->x = xIni + (hitpoints)* CASE_LENGHT;
					corRect->y = yIni;
					corRect->w = CASE_LENGHT;
					corRect->h = CASE_LENGHT;
					SDL_BlitSurface(screen, corRect, screen, dstCorRect);
				}
				if (yIni > yFinal)
				{
					dstCorRect->x = xIni;
					dstCorRect->y = yIni;
					corRect->x = xIni;
					corRect->y = yIni - CASE_LENGHT;
					corRect->w = (hitpoints)* CASE_SIZE + (hitpoints)* LINE_SIZE;
					corRect->h = CASE_LENGHT;
					SDL_BlitSurface(screen, corRect, screen, dstCorRect);
				}
				else if (yIni < yFinal)
				{
					dstCorRect->x = xIni;
					dstCorRect->y = yIni;
					corRect->x = xIni;
					corRect->y = yIni + CASE_LENGHT;
					corRect->w = (hitpoints)* CASE_SIZE + (hitpoints)* LINE_SIZE;
					corRect->h = CASE_LENGHT;
					SDL_BlitSurface(screen, corRect, screen, dstCorRect);
				}
			}
		}	
	}	
}

SDL_Surface * Ships::LoadImage()
{
	SDL_Surface* image = IMG_Load(path);
	if (image == nullptr)
	{
		printf("Unable to load image at path: %s, SDL_Error: %s\n", path, SDL_GetError());
	}
	return image;
}

Ships::~Ships()
{
	delete srcRotRect;
	delete srcRect;
	delete dstRect;
	delete corRect;
	delete dstCorRect;
	SDL_FreeSurface(image);
}

void Ships::CoordToArray(int x, int y)
{
	coord[0] = (x - A1_X) / CASE_LENGHT;
	coord[1] = (y - A1_Y) / CASE_LENGHT;
}

void Ships::ArrayToCoord(int i, int j)
{
	coord[0] = A1_X + i * CASE_LENGHT;
	coord[1] = A1_Y + j * CASE_LENGHT;
}
