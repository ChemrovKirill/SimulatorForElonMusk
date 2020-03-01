#pragma once

#include "Object.h"

#define PI 3.1415f
#define RAD (PI / 180.f)

using namespace sf;

struct RigidBodyParameters {
	Vector2f position;
	float height;
	float width;
	float angle;

	float mass;
	Vector2f mass_position; //принимает значения от 0 до 1
	float moment_of_inertia;

	Vector2f velocity;
	Vector2f acceleration;

	float angle_velocity;
	float angle_acceleration;

	RigidBodyParameters();
	RigidBodyParameters(const Vector2f new_position,
		const float& w, const float& h, const float& start_angle,
		const float& start_mass, const float& start_moment_of_inertia,
		const Vector2f& start_mass_position);
	RigidBodyParameters(const Vector2f new_position,
		const float& w, const float& h, const float& start_angle,
		const float& start_mass, const float& start_moment_of_inertia,
		const Vector2f& start_mass_position, const Vector2f& start_velocity,
		const Vector2f& start_acceleration, const float& start_angle_velocity,
		const float& start_angle_acceleration);
};

class RigidBody : public Object {
private:
	float mass;
	Vector2f mass_position; //принимает значения от 0 до 1
	float moment_of_inertia;

	Vector2f velocity;
	Vector2f acceleration;

	float angle_velocity;
	float angle_acceleration;
public:
	RigidBody(const String& f, const RigidBodyParameters& parameters);

	float GetMass() const;
	float GetMomentOfInertia() const;
	Vector2f GetMassPosition() const;
	Vector2f GetVelocuty() const;
	Vector2f GetAcceleration() const;
	float GetAngleVelocity() const;
	float GetAngleAcceleration() const;
	
	void SetMass(const float& new_mass);
	void SetMomentOfInertia(const float& new_moment_of_inertia);
	void SetMassPosition(const Vector2f& new_mass_position);
	void SetVelocuty(const Vector2f& new_velocity);
	void SetAcceleration(const Vector2f& new_acceleration);
	void SetAngleVelocity(const float& new_angle_velocity);
	void SetAngleAcceleration(const float& new_angle_acceleration);

	void UpdatePosition(const float& dt);
};