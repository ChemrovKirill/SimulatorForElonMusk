#pragma once
#include "Object.h"
#include "map"
#include <iomanip>
#include <sstream>

class SettingsItem {
private:
	Object item;
	Object left;
	Object right;
	int value;
	Font font;
	Text item_text;
	Text val_text;
	Vector2f position;
	String name;
public:
	SettingsItem(const SettingsItem& si) :
		SettingsItem(si.position, si.name) {}
	SettingsItem() :
		SettingsItem({ 0, 0 }, "") {}
	SettingsItem(const Vector2f& pos, const String& s) :
		position(pos), name(s),
		item("SettingsItem.png", pos, 725, 100, 0),
		left("ArrowLeft.png", { pos.x + item.GetWidth() - 150, pos.y }, 30, 65, 0),
		right("ArrowRight.png", { pos.x + item.GetWidth() - 20, pos.y }, 30, 65, 0),
		value(0) {
		font.loadFromFile("fonts/FRAHV.ttf");
		item_text = Text(s, font, 65);
		item_text.setPosition({ pos.x+10, pos.y+10});
		
		std::stringstream ss;
		ss << std::setw(3) << std::setfill('0') << value;
		val_text = Text(ss.str(), font, 50);
		val_text.setPosition({ left.GetPosition().x + 35, pos.y + 5 });
	}
	//SettingsItem operator = (const SettingsItem& si) {
	//	//item.SetPosition(si.position, 0);
	//	//left.SetPosition(si.left.GetPosition(), 0);
	//	//right.SetPosition(si.right.GetPosition(), 0);
	//	//item_text.setPosition(si.item_text.getPosition());
	//	//val_text.setPosition(si.val_text.getPosition());
	//	//value = si.value;
	//	return (*this);
	//}
	void Draw(RenderWindow& window) const {
		item.Draw(window);
		left.Draw(window);
		right.Draw(window);
		window.draw(item_text);
		window.draw(val_text);
	}
};

//class PlanetSettings {
//private:
//	std::map<
//public:
//
//};