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
	forces[name].exist = true;
}
void Ship::EngineOff(const std::string& name) { 
	engines[name].SetOff();
	forces[name].exist = false;
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
	if (isDestroyed) {
		return;
	}
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

void Ship::Destroy() {
	isDestroyed = true;
	sprite.setColor(Color::Red);
}

void Ship::updateAirForce(float k) {
	k /= 20.0;
	forces["Air"].force = k * sqal(velocity) / 10;

	if (sqal(velocity) > 1) {
		forces["Air"].force_vector = -rotate_to_angle(velocity, -GetAngle() * RAD) / sqal(velocity);
	}
	else {
		forces["Air"].force_vector = -rotate_to_angle(velocity, -GetAngle() * RAD);
	}


	if (angle_velocity > 10) {
		forces["AirLeft"].force_vector = Vector2f(0, 1);
		forces["AirRight"].force_vector = Vector2f(0, -1);

		forces["AirLeft"].force = k * angle_velocity / 10;
		forces["AirRight"].force = k * angle_velocity / 10;
	}
	else if (angle_velocity < -10) {
		forces["AirLeft"].force_vector = Vector2f(0, 1);
		forces["AirRight"].force_vector = Vector2f(0, -1);

		forces["AirLeft"].force = k * angle_velocity / 10;
		forces["AirRight"].force = k * angle_velocity / 10;
	}
	else {
		forces["AirLeft"].force_vector = Vector2f(0, 0);
		forces["AirRight"].force_vector = Vector2f(0, 0);

		forces["AirLeft"].force = 0;
		forces["AirRight"].force = 0;
	}
}

void Ship::draw_all(RenderWindow& window, bool position, bool speed, bool way, bool _forces, bool collision) {
	if (position == true) {
		DrawMassPosition(window);
	}
	if (way == true) {
		DrawBodyWay(window);
	}
	
	if (speed == true) {
		DrawSpeed(window);
	}
	if (_forces == true) {
		for (auto i : Ship::forces) {
			DrawForce(window, i.second);
		}
	}
	if (collision == true) {
		CollisionModelDraw(window);
	}
}

void Ship::AddMainForces(float gravity) {
	AddForce("G", Force(true, 0, Vector2f(0, 4 * gravity), Vector2f(0, 0)));
	ForceOn("G");

	AddForce("Air", Force(false, sqal(velocity), Vector2f(0, 0), Vector2f(0.5, 0.5)));
	ForceOn("Air");
	AddForce("AirLeft", Force(false, 0, Vector2f(0, 0), Vector2f(0, 0.5)));
	ForceOn("AirLeft");
	AddForce("AirRight", Force(false, 0, Vector2f(0, 0), Vector2f(1, 0.5)));
	ForceOn("AirRight");
}
