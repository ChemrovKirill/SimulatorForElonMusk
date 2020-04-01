#include "Engine.h"

Engine::Engine() : on(false), relative_position(0, 0), max_thrust_angle(0), thrust_angle(0), thrust(0), engine_vector(0, 0) {}
Engine::Engine(const Object& object, const Vector2f& start_rel_pos, const Force& start_force, const float& start_max_thrust_angle)
	: Object(object.GetFile(), object.GetPosition(), object.GetWidth(), object.GetHeight(), object.GetAngle()),
	on(false), relative_position(start_rel_pos), force(Force(start_force)),
	max_thrust_angle(start_max_thrust_angle), thrust_angle(0), thrust(1), engine_vector(start_force.force_vector) {}
Engine::Engine(const Engine& e) : Object(e.GetFile(), e.GetPosition(), e.GetWidth(), e.GetHeight(), e.GetAngle()),
on(e.on), relative_position(e.relative_position), force(e.force), max_thrust_angle(e.max_thrust_angle), thrust_angle(e.thrust_angle),
thrust(e.thrust), engine_vector(e.force.force_vector) {}

Force Engine::GetForce() const { return force; }
Vector2f Engine::GetRelPos() const { return relative_position; }
float Engine::GetThrust() const { return thrust; }
float Engine::GetThrustAngle() const { return thrust_angle; }
float Engine::GetMaxThrustAngle() const { return max_thrust_angle; }
Vector2f Engine::GetEngineVector() const { return engine_vector; }

void Engine::SetRelPos(const Vector2f& new_relative_position) { relative_position = new_relative_position; }
void Engine::SetThrust(const float& new_thrust) { thrust = new_thrust; }
void Engine::SetThrustAngle(const float& new_thrust_angle) { thrust_angle = new_thrust_angle; }
void Engine::SetMaxThrustAngle(const float& new_max_thrust_angle) { max_thrust_angle = new_max_thrust_angle; }
void Engine::SetEngineVector(const Vector2f& new_engine_vector) { engine_vector = new_engine_vector; }

bool Engine::If_on() const { return on; }
void Engine::SetOn() { on = true; force.exist = true; }
void Engine::SetOff() { on = false; force.exist = false; }

Engine Engine::operator = (const Engine& e) {
	force.exist = e.force.exist;
	force.is_force_field = e.force.is_force_field;
	force.force = e.force.force;
	force.force_vector = e.force.force_vector;
	force.force_point = e.force.force_point;

	on = e.on;
	thrust = e.thrust;
	thrust_angle = e.thrust_angle;
	max_thrust_angle = e.max_thrust_angle;
	relative_position = e.relative_position;

	file = e.file;
	width = e.width;
	height = e.height;
	angle = e.angle;
	exist = e.exist;
	position = e.position;
	engine_vector = e.engine_vector;
	//buffer.loadFromFile("sounds/" + f_sound);
	//sound.setBuffer(buffer);
	image.loadFromFile("images/" + file);
	image.createMaskFromColor(Color(0, 0, 0));
	texture.loadFromImage(image);
	sprite.setTexture(texture);
	sprite.setTextureRect(IntRect(0, 0, width, height));
	sprite.setPosition(position.x, position.y);
	sprite.rotate(angle);
	return e;
}