#include "ShipStand.h"

ShipStand::ShipStand(const ShipStand& SS)
	: ShipStand(SS.ship_file, SS.name, SS.position) {}

ShipStand::ShipStand(const String& f, const String& _name, const Vector2f& pos)\
	: name(_name), ship_file(f),
	ship(f, { 0,0 }, 0),
	Object("ShipStand.png", pos, 0) {
	float ship_x = position.x + (width - ship.GetWidth()) / 2;
	float ship_y = position.y + (height - ship.GetHeight()) / 2 - 30;
	ship.SetPosition({ ship_x, ship_y }, 0);
	font.loadFromFile("fonts/FRAHV.ttf");
	name_text = Text(name, font, 35);
	name_text.setPosition({ position.x + width / 2 - name_text.getLocalBounds().width / 2,
					position.y + height - 50 });
}

void ShipStand::SetSelected(bool selected) {
	if (selected) {
		SetColor(sel_color);
		name_text.setFillColor(Color(0xffffffff));
	}
	else {
		SetColor(not_sel_color);
		name_text.setFillColor(Color(0xffffffdf));
	}
}

void ShipStand::SetChosen(bool chosen) {
	if (chosen) {
		name_text.setFillColor(sel_color);
	}
	else {
		name_text.setFillColor(Color(0xffffffff));
	}
}

void ShipStand::Draw(RenderWindow& window) const {
	ship.Draw(window);
	Object::Draw(window);
	window.draw(name_text);
}
