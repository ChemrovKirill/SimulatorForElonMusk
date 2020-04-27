#pragma once
#include "Object.h"

class Button : public Object {
private:
	Font font;
	Text text;
	String name;
public:
	Button(const Button& b) : Button(b.name, b.GetPosition()) {}
	Button(const String& _name, const Vector2f& position) :
		Object("Button.png", position, 350, 100, 0),
		name(_name) {
		font.loadFromFile("fonts/FRAHV.ttf");
		text = Text(name, font, 65);
		text.setPosition({ position.x + width/2 - text.getLocalBounds().width/2,
						   position.y + height/2 - text.getLocalBounds().height / 2 -15 });
	}
	void Draw(RenderWindow& window) const {
		Object::Draw(window);
		window.draw(text);
	}
	void SetColor(const Color& c) {
		Object::SetColor(c);
		text.setFillColor(Color(c.toInteger() | 0x000000ff));
	}
};