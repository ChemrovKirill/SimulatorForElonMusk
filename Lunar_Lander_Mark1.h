#pragma once

#include "Ship.h"
#include <fstream>
#include <exception>

class Lunar_Lander_Mark1 : public Ship {
private:
public:
	Lunar_Lander_Mark1(sf::Vector2f position);

	RigidBodyParameters download(sf::Vector2f position);
	void assembly();

	void control();
	void drow_all(RenderWindow& window, bool position, bool speed, bool way, bool forces, bool collision);

};
