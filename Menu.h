#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "Object.h"
#include "Surface.h"
#include "Ship.h"
#include "SettingsItem.h"
#include <map>
#include "Button.h"

#include "Tests.h"

#include "Lunar_Lander_Mark1.h"
#include "Lunar_Lander_Mark1_STM32.h"
#include "RickAndMorty.h"


#include "Usart.h"


void Menu(RenderWindow& window);
void StartGame(RenderWindow& window);
Surface PlanetSelection(RenderWindow& window, bool& if_back);
//Ship ShipBuilding(RenderWindow& window);