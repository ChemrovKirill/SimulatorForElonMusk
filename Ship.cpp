#include "Ship.h"
#include "iostream"

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