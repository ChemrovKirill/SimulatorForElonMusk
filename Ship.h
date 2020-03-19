#pragma once
#include "RigidBody.h"
#include <cmath>

							   //													   ^
class Engine : public Object { //force_vector calculated from the original angle: ---- | ---- - 0 grad, ---- -> ---- - 90 grad
private:
	Vector2f relative_position;
	Force force;
	bool on;
	float thrust; //from 0 (0%) to 1 (100%) of force.force
	float thrust_angle; //from -1 (-100%) to 1 (100%) of max_thrust_angle
	float max_thrust_angle; //the angle at which the engine can deviate
public:
	Engine();
	Engine(const Object& object,  const Vector2f& start_rel_pos, const Force& start_force, const float& start_max_thrust_angle);
	Engine(const Engine& e);

	Force GetForce() const;
	Vector2f GetRelPos() const;
	float GetThrust() const;
	float GetThrustAngle() const;
	float GetMaxThrustAngle() const;

	void SetRelPos(const Vector2f& new_relative_position);
	void SetThrust(const float& new_thrust);
	void SetThrustAngle(const float& new_thrust_angle);
	void SetMaxThrustAngle(const float& new_max_thrust_angle);

	bool If_on() const;
	void SetOn();
	void SetOff();

	Engine operator = (const Engine&);
};



class Ship : public RigidBody {
private:
	std::map<std::string, Engine> engines;
public:
	Ship(const String& f, const RigidBodyParameters& parameters);

	void AddEngine(const Engine& new_engine, const std::string& name);
	void EngineOn(const std::string& name);
	void EngineOff(const std::string& name);
	void SetEngineThrust(const std::string& name, float new_thrust);
	void SetEngineThrustAngle(const std::string& name, float new_thrust_angle);

	void UpdateEngines(const std::string& name);
	void UpdateShipPosition(const float& dt);
	void UpdateEnginesPosition(const std::string& name, const Vector2f& new_position);

	void DrawShip(RenderWindow& window) const;
};