#pragma once

#include "Object.h"

using namespace sf;

class RigidBody : public Object {
private:
	float mass;
	Vector2f mass_position;
	float moment_of_inertia;

	Vector2f velocity;
	Vector2f acceleration;

	Vector2f angle_velocity;
	Vector2f angle_acceleration;
public:
	float GetMass() const;
	float GetMomentOfInertia() const;
	Vector2f GetMassPosition() const;
	Vector2f GetVelocuty() const;
	Vector2f GetAcceleration() const;
	Vector2f GetAngleVelocity() const;
	Vector2f GetAngleAcceleration() const;
	
	void SetMass(const float& new_mass);
	void SetMomentOfInertia(const float& new_moment_of_inertia);
	void SetMassPosition(const Vector2f& new_mass_position);
	void SetVelocuty(const Vector2f& new_velocity);
	void SetAcceleration(const Vector2f& new_acceleration);
	void SetAngleVelocity(const Vector2f& new_angle_velocity);
	void SetAngleAcceleration(const Vector2f& new_angle_acceleration);
};