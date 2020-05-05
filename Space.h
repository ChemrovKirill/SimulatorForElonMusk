#pragma once
#include <SFML/Graphics.hpp>
#include "Surface.h"

using namespace sf;

class Space {
private:
	String file;
	Image image;
	Texture texture;
	Sprite sprite;
	std::vector<Object> bodies;
	std::vector<Vector2f> positions;
	Vector2f start_pos;
public:
	Space(const String& f, const Vector2f&);
	void Update(const View& view);
	void Draw(RenderWindow& window) const;
};