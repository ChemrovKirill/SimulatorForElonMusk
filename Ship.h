#pragma once
#include "RigidBody.h"
#include "Engine.h"
#include <cmath>

class Ship : public RigidBody {
private:
	bool isDestroyed = false;
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
	void UpdateEnginesPosition(const std::string& name, const sf::Vector2f& new_position);

	void DrawShip(RenderWindow& window) const;
	void Destroy();
};