#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "GeomShapesLib/GeomShapes.h"
#include <vector>

#define PI 3.1415f
#define RAD (PI / 180.f)

using namespace sf;

class Object {
protected:
	Vector2f position;
	float height, width, angle;
	std::vector<Vector2f> vertexes;
	bool exist = true;
	String file;
	Image image;
	Texture texture;
	Sprite sprite;

	SoundBuffer buffer;
	Sound sound;
public:
	Object() : height(0), width(0), angle(0) {}
	Object(const String& f, const Vector2f new_position,
		const float& w, const float& h, const float& start_angle); //косяк с углом!!!

	bool Exist() const;
	Vector2f GetPosition() const;
	float GetHeight() const;
	float GetWidth() const;
	float GetAngle() const;
	void VertexesUpdate();
	std::vector<Vector2f> GetVertexes() const ;

	bool PointInside(const Vector2f& point) const;

	void SetHeight(const float& new_height);
	void SetWidth(const float& new_width);

	void SetPosition(const Vector2f& new_position, const float& new_angle);
	virtual void Draw(RenderWindow& window) const;
};