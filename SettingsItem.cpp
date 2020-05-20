#include "SettingsItem.h"


SettingsItem::SettingsItem(const SettingsItem& si)
	: SettingsItem::SettingsItem(si.position, si.name, si.value) {}

SettingsItem::SettingsItem()
	: SettingsItem({ 0, 0 }, "") {}

SettingsItem::SettingsItem(const Vector2f& pos, const String& s, const int& val) 
	: SettingsItem(pos, s) { 
	value = val;
}

SettingsItem::SettingsItem(const Vector2f& pos, const String& s) :
	position(pos), name(s),
	Object("SettingsItem.png", pos, 600, 80, 0),
	left("ArrowLeft.png", { pos.x + width - 145, pos.y }, 30, 60, 0),
	right("ArrowRight.png", { pos.x + width - 15, pos.y }, 30, 60, 0),
	value(0)
{
	font.loadFromFile("fonts/FRAHV.ttf");
	item_text = Text(s, font, 50);
	item_text.setPosition({ pos.x + 10, pos.y + 10 });

	std::stringstream ss;
	ss << std::setw(3) << std::setfill('0') << value;
	val_text = Text(ss.str(), font, 50);
	val_text.setPosition({ left.GetPosition().x + 35, pos.y });
}

void SettingsItem::Draw(RenderWindow& window) const {
	Object::Draw(window);
	left.Draw(window);
	right.Draw(window);
	window.draw(item_text);
	window.draw(val_text);
}

void SettingsItem::Inc(const int& n) {
	if (value >= 100) {
		return;
	}
	value += n;
	Update();
}

void SettingsItem::Dec(const int& n) {
	if (value <= 0) {
		return;
	}
	value -= n;
	SettingsItem::Update();
}
void SettingsItem::SetValue(const int& n) {
	if (n > 100 || n < 0) {
		return;
	}
	value = n;
	Update();
}

int SettingsItem::GetValue() const {
	return value;
}

void SettingsItem::Update() {
	std::stringstream ss;
	ss << std::setw(3) << std::setfill('0') << value;
	val_text.setString(ss.str());
}

void SettingsItem::SetSelected(bool selected) {
	if (selected) {
		SetColor(sel_color);
		right.SetColor(sel_color);
		left.SetColor(sel_color);
		item_text.setFillColor(Color(0xffffffff));
		val_text.setFillColor(Color(0xffffffff));
	}
	else {
		SetColor(not_sel_color);
		right.SetColor(not_sel_color);
		left.SetColor(not_sel_color);
		item_text.setFillColor(Color(0xffffffdf));
		val_text.setFillColor(Color(0xffffffdf));
	}
}

Object SettingsItem::GetLeft() const { 
	return left; 
}

Object SettingsItem::GetRight() const { 
	return right; 
}