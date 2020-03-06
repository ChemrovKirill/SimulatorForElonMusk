#pragma once
#include "RigidBody.h"

class Engine : public Object {
private:
	Vector2f relative_position;
	Force force;
	bool on;
	bool if_controled = false;
public:
	Engine() : on(false), relative_position(0, 0) {}
	Engine(const Object& object, const Vector2f& rel_pos, const float& force_value)
		: Object(object), on(false), relative_position(rel_pos), force(Force(0, force_value, Vector2f(0, -1), rel_pos)) {}

	Force GetForce() const { return force; }
	bool If_on() const { return on; }
	void SetOn() { on = true; force.exist = true; }
	void SetOff() { on = false; force.exist = false; }
	Vector2f GetRelPos() const { return relative_position; }
};



class Ship : public RigidBody {
private:
	std::map<std::string, Engine> engines;
public:
	Ship(const RigidBody& rb, std::map<std::string, Engine>& _engines);
	void Draw(RenderWindow& window) const;
	void Control();
	void UpdatePosition(const float&);
};