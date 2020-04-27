#pragma once
#include "Object.h"

class Button : public Object {
private:
	Font font;
	Text text;
	String name;
	Color sel_color = Color(0x0000f0ff);
	Color not_sel_color = Color(0x0000f080);
public:
	Button(const Button& b);
	Button(const String& _name, const Vector2f& position);
	void Draw(RenderWindow& window) const;
	void SetColor(const Color& c);
	void SetSelected(bool selected);
};