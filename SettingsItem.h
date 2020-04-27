#pragma once
#include "Object.h"
#include "map"
#include <iomanip>
#include <sstream>

class SettingsItem : public Object{
private:
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
		Object("SettingsItem.png", pos, 725, 100, 0),
		left("ArrowLeft.png", { pos.x + width - 150, pos.y }, 30, 65, 0),
		right("ArrowRight.png", { pos.x + width - 20, pos.y }, 30, 65, 0),
		value(0) 
	{
		font.loadFromFile("fonts/FRAHV.ttf");
		item_text = Text(s, font, 60);
		item_text.setPosition({ pos.x+10, pos.y+10});
		
		std::stringstream ss;
		ss << std::setw(3) << std::setfill('0') << value;
		val_text = Text(ss.str(), font, 50);
		val_text.setPosition({ left.GetPosition().x + 35, pos.y + 5 });
	}
	void Draw(RenderWindow& window) const {
		Object::Draw(window);
		left.Draw(window);
		right.Draw(window);
		window.draw(item_text);
		window.draw(val_text);
	}
	void Inc(const int& n) {
		if (value >= 100) {
			return;
		}
		value += n;
		Update();
	}
	void Dec(const int& n) {
		if (value <= 0) {
			return;
		}
		value -= n;
		Update();
	}
	void SetValue(const int& n) {
		if (n > 100 || n < 0) {
			return;
		}
		value = n;
		Update();
	}
	int GetValue() const {
		return value;
	}
	void Update() {
		std::stringstream ss;
		ss << std::setw(3) << std::setfill('0') << value;
		val_text.setString(ss.str());
	}
	Object GetLeft() { return left; }
	Object GetRight() { return right; }

};

//class PlanetSettings {
//private:
//	std::map<
//public:
//
//};