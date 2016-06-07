#include "BattleShips.h"

BattleShips::BattleShips()
{
	window = nullptr;
	screen = nullptr;
	carrier = nullptr;
	battheship = nullptr;
	cruiser = nullptr;
	submarine = nullptr;
	destroyer = nullptr;
	seaPlayer1 = nullptr;
	seaPlayer1 = nullptr;

	if (SDL_Init(SDL_INIT_VIDEO) > 0)
	{
		printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
	}
	else
	{
		window = SDL_CreateWindow(
			TITLE, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
			SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);

		if (window == nullptr)
		{
			printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
		}
		else
		{
			screen = SDL_GetWindowSurface(window);
			SDL_FillRect(screen, nullptr, SDL_MapRGB(screen->format, 0, 0, 0));
		}
	}

	fleet.push_back(carrier = new Ships(CARRIER));
	fleet.push_back(battheship = new Ships(BATTLESHIP));
	fleet.push_back(cruiser = new Ships(CRUISER));
	fleet.push_back(submarine = new Ships(SUBMARINE));
	fleet.push_back(destroyer = new Ships(DESTROYER));

	seaPlayer1 = new Sea(screen, window);
	seaPlayer2 = new Sea(screen, window);

	seaPlayer1->DrawSea(screen);

	for (int i = CARRIER; i <= DESTROYER; i++)
	{
		PlaceShip(screen, seaPlayer1, window, fleet.at(i));
	}

	SDL_DestroyWindow(window);
	SDL_Quit();
}

void BattleShips::PlaceShip(SDL_Surface * screen, Sea * sea, SDL_Window * window, Ships* ship)
{
	SDL_Event e;
	bool isRunning = true;
	bool isChoosing = true;

	int shipPosX = A1_X;
	int shipPosY = A1_Y;

	bool isRotated = false;
	bool isRotating = false;
	sea->PlaceShip(screen, ship, shipPosX, shipPosY, isRotated);

	while (isRunning)
	{
		while (SDL_PollEvent(&e) != 0)
		{
			if (e.type == SDL_KEYDOWN)
			{
				if (e.key.keysym.sym == SDLK_RETURN)
				{
					sea->FillGrid(ship, shipPosX, shipPosY, isRotated);
					isRunning = false;
				}
				else if (e.type == SDL_KEYDOWN)
				{
					switch (e.key.keysym.sym)
					{
					case SDLK_DOWN:
						if (isRotated)
						{
							if (shipPosY < A1_Y + (LINE_SIZE + (LINE_SIZE - ship->GetHitPoints())) * CASE_LENGHT && sea->PositionAvailable(ship, shipPosX, shipPosY + CASE_LENGHT, isRotated))
							{
								sea->EraseShip(screen, ship, shipPosX, shipPosY, shipPosX, shipPosY + CASE_LENGHT, isRotated, isRotating);
								shipPosY += CASE_LENGHT;
								sea->PlaceShip(screen, ship, shipPosX, shipPosY, isRotated);
							}
						}
						else
						{
							if (shipPosY < A1_Y + GRID_LENGHT * CASE_LENGHT - CASE_LENGHT && sea->PositionAvailable(ship, shipPosX, shipPosY + CASE_LENGHT, isRotated))
							{
								sea->EraseShip(screen, ship, shipPosX, shipPosY, shipPosX, shipPosY + CASE_LENGHT, isRotated, isRotating);
								shipPosY += CASE_LENGHT;
								sea->PlaceShip(screen, ship, shipPosX, shipPosY, isRotated);
							}
						}
						break;
					case SDLK_UP:
						if (isRotated)
						{
							if (shipPosY > A1_Y && sea->PositionAvailable(ship, shipPosX, shipPosY - CASE_LENGHT, isRotated))
							{
								sea->EraseShip(screen, ship, shipPosX, shipPosY, shipPosX, shipPosY - CASE_LENGHT, isRotated, isRotating);
								shipPosY -= CASE_LENGHT;
								sea->PlaceShip(screen, ship, shipPosX, shipPosY, isRotated);
							}
						}
						else
						{
							if (shipPosY > A1_Y && sea->PositionAvailable(ship, shipPosX, shipPosY - CASE_LENGHT, isRotated))
							{
								sea->EraseShip(screen, ship, shipPosX, shipPosY, shipPosX, shipPosY - CASE_LENGHT, isRotated, isRotating);
								shipPosY -= CASE_LENGHT;
								sea->PlaceShip(screen, ship, shipPosX, shipPosY, isRotated);
							}
						}
						break;
					case SDLK_RIGHT:
						if (isRotated)
						{
							if (shipPosX < A1_X + GRID_LENGHT * CASE_LENGHT - CASE_LENGHT && sea->PositionAvailable(ship, shipPosX + CASE_LENGHT, shipPosY, isRotated))
							{
								sea->EraseShip(screen, ship, shipPosX, shipPosY, shipPosX + CASE_LENGHT, shipPosY, isRotated, isRotating);
								shipPosX += CASE_LENGHT;
								sea->PlaceShip(screen, ship, shipPosX, shipPosY, isRotated);
							}
						}
						else
						{
							if (shipPosX < A1_X + (LINE_SIZE + (LINE_SIZE - ship->GetHitPoints())) * CASE_LENGHT && sea->PositionAvailable(ship, shipPosX + CASE_LENGHT, shipPosY, isRotated))
							{
								sea->EraseShip(screen, ship, shipPosX, shipPosY, shipPosX + CASE_LENGHT, shipPosY, isRotated, isRotating);
								shipPosX += CASE_LENGHT;
								sea->PlaceShip(screen, ship, shipPosX, shipPosY, isRotated);
							}
						}
						break;
					case SDLK_LEFT:
						if (isRotated)
						{
							if (shipPosX > A1_X && sea->PositionAvailable(ship, shipPosX - CASE_LENGHT, shipPosY, isRotated))
							{
								sea->EraseShip(screen, ship, shipPosX, shipPosY, shipPosX - CASE_LENGHT, shipPosY, isRotated, isRotating);
								shipPosX -= CASE_LENGHT;
								sea->PlaceShip(screen, ship, shipPosX, shipPosY, isRotated);
							}
						}
						else
						{
							if (shipPosX > A1_X && sea->PositionAvailable(ship, shipPosX - CASE_LENGHT, shipPosY, isRotated))
							{
								sea->EraseShip(screen, ship, shipPosX, shipPosY, shipPosX - CASE_LENGHT, shipPosY, isRotated, isRotating);
								shipPosX -= CASE_LENGHT;
								sea->PlaceShip(screen, ship, shipPosX, shipPosY, isRotated);
							}
						}
						break;
					case SDLK_SPACE:
						bool rot;
						if (isRotated)
						{
							rot = false;
						}
						else
						{
							rot = true;
						}
						if (isRotated && sea->PositionAvailable(ship, shipPosX, shipPosY, rot))
						{
							isRotating = true;
							sea->EraseShip(screen, ship, shipPosX, shipPosY, shipPosX, shipPosY, isRotated, isRotating);
							isRotated = false;
							sea->PlaceShip(screen, ship, shipPosX, shipPosY, isRotated);
							isRotating = false;
						}
						else if (sea->PositionAvailable(ship, shipPosX, shipPosY, rot))
						{
							isRotating = true;
							sea->EraseShip(screen, ship, shipPosX, shipPosY, shipPosX, shipPosY, isRotated, isRotating);
							isRotated = true;
							sea->PlaceShip(screen, ship, shipPosX, shipPosY, isRotated);
							isRotating = false;
						}
						break;
					default:
						break;
					}
				}
			}			
		}
		SDL_UpdateWindowSurface(window);
	}
}


BattleShips::~BattleShips()
{
	delete carrier;
	delete battheship;
	delete cruiser;
	delete submarine;
	delete destroyer;
	delete seaPlayer1;
	delete seaPlayer2;
}
