#pragma once

#include "Ship.h"
#include <fstream>
#include <exception>

class Dron : public Ship {
private:
public:
	Dron(sf::Vector2f position);

	RigidBodyParameters download(sf::Vector2f position);
	void assembly();
	void control();
	virtual void DrawShip(RenderWindow& window) const;
};
