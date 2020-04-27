#pragma once

#include "Ship.h"
#include <fstream>
#include <exception>

class RickAndMorty : public Ship {
private:
public:
	RickAndMorty(sf::Vector2f position);

	RigidBodyParameters download(sf::Vector2f position);
	void assembly();

	void control();
	void draw_all(RenderWindow& window, bool position, bool speed, bool way, bool forces, bool collision);

};
