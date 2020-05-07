#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <map>
#include "Object.h"
#include "Surface.h"
#include "Space.h"
#include "Ship.h"
#include "SettingsItem.h"
#include "Button.h"

#include "Tests.h"

#include "Lunar_Lander_Mark1.h"
#include "Lunar_Lander_Mark1_STM32.h"
#include "RickAndMorty.h"


#include "Usart.h"


void Menu(RenderWindow& window);
void StartGame(RenderWindow& window);
Surface PlanetSelection(RenderWindow& window, bool& if_back);
bool PauseMenu(RenderWindow& window, bool& isPaused, View& view);
//Ship ShipBuilding(RenderWindow& window);