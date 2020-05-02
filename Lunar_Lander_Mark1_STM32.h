#pragma once

#include "Ship.h"
#include <fstream>
#include <exception>

#include "Usart.h"



class Lunar_Lander_Mark1_STM32 : public Ship {
public:


	Lunar_Lander_Mark1_STM32(sf::Vector2f position);

	RigidBodyParameters download(sf::Vector2f position);
	void assembly();
	void control_STM(const Lander_Parametr& par);
	void control();
};
