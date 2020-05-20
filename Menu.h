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
#include "ShipStand.h"

#include "Tests.h"
#include "SuperPuperShip.h"
#include "Lunar_Lander_Mark1.h"
#include "Lunar_Lander_Mark1_STM32.h"
#include "RickAndMorty.h"
#include "Dron.h"

#include "Usart.h"

extern int SoundVolume;
extern int MusicVolume;

void Menu(RenderWindow& window);
void StartGame(RenderWindow& window);
void Settings(RenderWindow& window, Music& music);
Surface PlanetSettings(RenderWindow& window, bool& if_back);
bool PauseMenu(RenderWindow& window, bool& isPause, bool& Restart, View& view);
Ship* ShipSettings(RenderWindow& window, const Vector2f&, bool& if_Menu);