#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

using namespace sf;

class Object {
private:
	Vector2f position;
	float height, width;
	bool exist = true;
	String file;
	Image image;
	Texture texture;
	Sprite sprite;
	SoundBuffer buffer;
	Sound sound;
public:
	
	Object(const String& f, const double& start_x,
		const double& start_y, const double& w, const double& h)
		: file(f), height(h), width(w), position(start_x, start_y) {
		//buffer.loadFromFile("sounds/" + f_sound);
		//sound.setBuffer(buffer);
		image.loadFromFile("images/" + f);
		image.createMaskFromColor(Color(0, 255, 0));
		texture.loadFromImage(image);
		sprite.setTexture(texture);
		sprite.setTextureRect(IntRect(0, 0, w, h));
		sprite.setPosition(position.x, position.y);
	}

	bool Exist() const { return exist; }
	double GetX() const { return position.x; }
	double GetY() const { return position.y; }
	double GetHeight() const { return height; }
	double GetWidth() const { return width; }
	void SetX(const double& new_x) { position.x = new_x; }
	void SetY(const double& new_y) { position.y = new_y; }
	void SetHeight(const double& new_height) { height = new_height; }
	void SetWidth(const double& new_width) { width = new_width; }
	void Draw(RenderWindow& window) { window.draw(sprite); }

};