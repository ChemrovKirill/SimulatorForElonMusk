#include "Button.h"

Button::Button(const Button& b) : Button(b.name, b.GetPosition()) {}
Button::Button(const String& _name, const Vector2f& position) :
	Object("Button.png", position, 350, 100, 0),
	name(_name) {
	font.loadFromFile("fonts/FRAHV.ttf");
	text = Text(name, font, 65);
	text.setPosition({ position.x + width / 2 - text.getLocalBounds().width / 2,
					   position.y + height / 2 - text.getLocalBounds().height / 2 - 10 });
}
void Button::Draw(RenderWindow& window) const {
	Object::Draw(window);
	window.draw(text);
}
void Button::SetColor(const Color& c) {
	Object::SetColor(c);
	text.setFillColor(Color(c.toInteger() | 0x000000ff));
}
void Button::SetSelected(bool selected) {
	if (selected) {
		SetColor(sel_color);
	}
	else {
		SetColor(not_sel_color);
	}
}