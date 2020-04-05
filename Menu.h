#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "Object.h"
#include "Surface.h"
#include "Ship.h"

void Menu(RenderWindow& window);
void StartGame(RenderWindow& window);
Surface SurfaceSelection(RenderWindow& window);
Ship ShipBuilding(RenderWindow& window);