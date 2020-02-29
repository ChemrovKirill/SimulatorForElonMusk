#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

using namespace sf;

class Object {
private:
	Vector2f position;
	float height, width, angle;
	bool exist = true;

	String file;
	Image image;
	Texture texture;
	Sprite sprite;

	SoundBuffer buffer;
	Sound sound;
public:
	Object(const String& f, const float& start_x, const float& start_y, 
		const float& w, const float& h, const float& start_angle)
		: file(f), height(h), width(w), position(start_x, start_y), angle(start_angle) {
		//buffer.loadFromFile("sounds/" + f_sound);
		//sound.setBuffer(buffer);
		image.loadFromFile("images/" + f);
		image.createMaskFromColor(Color(0, 255, 0));
		texture.loadFromImage(image);
		sprite.setTexture(texture);
		sprite.setTextureRect(IntRect(0, 0, w, h));
		sprite.setPosition(position.x, position.y);
		sprite.rotate(angle);
	}

	bool Exist() const { return exist; }
	float GetX() const { return position.x; }
	float GetY() const { return position.y; }
	float GetHeight() const { return height; }
	float GetWidth() const { return width; }
	float GetAngle() const { return angle; }

	void SetX(const float& new_x) { position.x = new_x; }
	void SetY(const float& new_y) { position.y = new_y; }
	void SetHeight(const float& new_height) { height = new_height; }
	void SetWidth(const float& new_width) { width = new_width; }
	void SetAngle(const float& new_angle) { angle = new_angle; }

	void Draw(RenderWindow& window) const { window.draw(sprite); }
	void Rotate(const float& new_angle) { sprite.rotate(new_angle); }
};