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
	virtual void DrawShip(RenderWindow& window) const;
};
