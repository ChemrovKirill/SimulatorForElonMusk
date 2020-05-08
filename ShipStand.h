#pragma once
#include "Object.h"

class ShipStand : public Object {
private:
	Object ship;
	Font font;
	Text name_text;
	String name;
	Color sel_color = Color(0x0000f0ff);
	Color not_sel_color = Color(0x0000f080);
	String ship_file;
public:
	ShipStand(const ShipStand& SS);
	ShipStand(const String& f, const String& _name, const Vector2f& pos);

	void SetSelected(bool selected);
	void SetChosen(bool chosen);
	void Draw(RenderWindow& window) const;
};