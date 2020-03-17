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

void Object::VertexesUpdate() {
	Vector2f p_1 = { width * cos(RAD * angle), width * sin(RAD * angle) };
	Vector2f p_2 = p_1 + Vector2f(-height * sin(RAD * angle), height * cos(RAD * angle));
	Vector2f p_3 = { height * cos(RAD * angle), height * sin(RAD * angle) };
	if (vertexes.size >= 4) {
		vertexes[0] = position;
		vertexes[1] = position + p_1;
		vertexes[2] = position + p_2;
		vertexes[3] = position + p_3;
	}
	else {
		vertexes.push_back(position);
		vertexes.push_back(position + p_1);
		vertexes.push_back(position + p_2);
		vertexes.push_back(position + p_3);
	}
}

std::vector<Vector2f> Object::GetVertexes() const {
	return vertexes;
}

bool Object::Exist() const { return exist; }
Vector2f Object::GetPosition() const { return position; }
float Object::GetHeight() const { return height; }
float Object::GetWidth() const { return width; }
float Object::GetAngle() const { return angle; }

void Object::SetHeight(const float& new_height) { height = new_height; }
void Object::SetWidth(const float& new_width) { width = new_width; }

void Object::SetPosition(const Vector2f& new_position, const float& new_angle) {
	sprite.setPosition(new_position.x, new_position.y);
	sprite.rotate(new_angle - angle);

	position = new_position;
	angle = new_angle;
	VertexesUpdate();
}
void Object::Draw(RenderWindow& window) const { window.draw(sprite); }
