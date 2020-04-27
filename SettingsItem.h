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
	Color sel_color = Color(0x0000f0ff);
	Color not_sel_color = Color(0x0000f080);
public:
	SettingsItem(const SettingsItem& si);
	SettingsItem();
	SettingsItem(const Vector2f& pos, const String& s);
	void Draw(RenderWindow& window) const;
	void Inc(const int& n);
	void Dec(const int& n);
	void SetValue(const int& n);
	int GetValue() const;
	void Update();
	void SetSelected(bool selected);
	Object GetLeft() const;
	Object GetRight() const;
};