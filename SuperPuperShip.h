#pragma once

#include "Ship.h"
#include <fstream>
#include <exception>

class SuperPuperShip : public Ship {
private:
public:
	SuperPuperShip(sf::Vector2f position);

	RigidBodyParameters download(sf::Vector2f position);
	void assembly();
	void control();
	virtual void DrawShip(RenderWindow& window) const;
};

