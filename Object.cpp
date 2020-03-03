#include "Object.h"

using namespace sf;

Object::Object(const String& f, const Vector2f new_position,
	const float& w, const float& h, const float& start_angle)
	: file(f), height(h), width(w), position(new_position), angle(start_angle) {
	//buffer.loadFromFile("sounds/" + f_sound);
	//sound.setBuffer(buffer);
	image.loadFromFile("images/" + f);
	image.createMaskFromColor(Color(0, 0, 0));
	texture.loadFromImage(image);
	sprite.setTexture(texture);
	sprite.setTextureRect(IntRect(0, 0, w, h));
	sprite.setPosition(position.x, position.y);
	sprite.rotate(angle); 
}

bool Object::Exist() const { return exist; }
Vector2f Object::GetPosition() const { return position; }
float Object::GetHeight() const { return height; }
float Object::GetWidth() const { return width; }
float Object::GetAngle() const { return angle; }

void Object::SetPosition(const Vector2f& new_position) { position = new_position; }
void Object::SetHeight(const float& new_height) { height = new_height; }
void Object::SetWidth(const float& new_width) { width = new_width; }
void Object::SetAngle(const float& new_angle) { angle = new_angle; }

void Object::SetObjectPosition(const Vector2f& new_position, const float& new_angle) {
	sprite.setPosition(new_position.x, new_position.y);
	sprite.rotate(new_angle - angle);

	SetPosition(new_position);
	SetAngle(new_angle);
}
void Object::Draw(RenderWindow& window) const { window.draw(sprite); }
void Object::Rotate(const float& new_angle) { sprite.rotate(new_angle); }
