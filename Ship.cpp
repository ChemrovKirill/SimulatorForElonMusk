#include "Ship.h"
#include "iostream"


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




Ship::Ship(const String& f, const RigidBodyParameters& parameters)
	: RigidBody(f, parameters) {}

void Ship::AddEngine(const Engine& new_engine, const std::string& name) { 
	engines[name] = new_engine; 
	AddForce(name, engines[name].GetForce());
	UpdateEngines(name);
}
void Ship::EngineOn(const std::string& name) {
	engines[name].SetOn(); 

}
void Ship::EngineOff(const std::string& name) { 
	engines[name].SetOff();
}
void Ship::SetEngineThrust(const std::string& name, float new_thrust) { 
	engines[name].SetThrust(new_thrust); 
	UpdateEngines(name);
}
void Ship::SetEngineThrustAngle(const std::string& name, float new_thrust_angle) { 
	engines[name].SetThrustAngle(new_thrust_angle);
	UpdateEngines(name);
}

void Ship::UpdateEngines(const std::string& name) {
	forces[name].force = engines[name].GetForce().force * engines[name].GetThrust();
	
	forces[name].force_vector.x = cos(acos(engines[name].GetEngineVector().x) - RAD * engines[name].GetMaxThrustAngle() * engines[name].GetThrustAngle());
	forces[name].force_vector.y = sin(asin(engines[name].GetEngineVector().y) - RAD * engines[name].GetMaxThrustAngle() * engines[name].GetThrustAngle());
}

void Ship::UpdateShipPosition(const float& dt) {
	UpdatePosition(dt);
	for (const auto& e : engines) {
		UpdateEnginesPosition(e.first, GetPosition());
	}
}

void Ship::UpdateEnginesPosition(const std::string& name, const Vector2f& new_position) {
	float x, y;
	float fb;
	x = GetWidth() * engines[name].GetRelPos().x - engines[name].GetWidth() * 0.5;
	y = GetHeight() * engines[name].GetRelPos().y - engines[name].GetHeight() * 0.5;

	float diag_engine = sqrt(pow(x, 2) + pow(y, 2));

	if (x >= 0 && y != 0) { fb = atan(y / x); }
	else if (x < 0) { fb = atan(y / x) - PI; }
	else { fb = 0; }

	engines[name].SetPosition(Vector2f(
		new_position.x + cos(RAD * GetAngle() + fb) * diag_engine,
		new_position.y + sin(RAD * GetAngle() + fb) * diag_engine),
		angle + engines[name].GetMaxThrustAngle() * engines[name].GetThrustAngle()
	);
}

void Ship::DrawShip(RenderWindow& window) const {
	Draw(window);
	for (const auto& e : engines) {
		e.second.Draw(window);
	}
}