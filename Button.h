#pragma once
#include "Object.h"

class Button {
private:
	Object frame;
	Font font;
	Text text;
public:
	Button(const String& name, const Vector2f& position) :
	frame("Button.png", position, 350, 100, 0) {
		font.loadFromFile("fonts/FRAHV.ttf");
		text = Text(name, font, 65);
		text.setPosition({ position.x + 10, position.y + 10 });
	}

};