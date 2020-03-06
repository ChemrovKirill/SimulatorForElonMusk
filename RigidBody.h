#pragma once

#include "Object.h"
#include <cmath>
#include <set>
#include <string>

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

struct Force {
	bool exist;
	bool is_force_field;

	float force;
	Vector2f force_vector; //если сила создает поле, то вектор - напряженность поля, иначе
						   //единичный вектор, направленный относительно ориентации коробля: 
						   //(0,-1) - вверх относительно носа, (0,1) - вниз, (1,0) - вправо, (-1,0) - влево
	Vector2f force_point;  //точка приложения силы, принимает значения от 0 до 1

	Force();
	Force(bool field, float new_force, Vector2f start_vector, Vector2f start_force_point);
	Force operator = (const Force&);
};

class RigidBody : public Object {
protected:
	float mass;
	Vector2f mass_position; //принимает значения от 0 до 1
	float moment_of_inertia; //Добавить авторассчет момента инерции и запихать в класс арктангенс и diag!!!

	Vector2f velocity;
	Vector2f acceleration;

	float angle_velocity;
	float angle_acceleration;

	std::map<String,Force> forces; //Переделать в set!!!
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

	virtual void UpdatePosition(const float& dt);
	void AddForce(const Force& new_force, const std::string& name);
	void ForceOn(const std::string& name);
	void ForceOff(const std::string& name);
	void UpdateForces();
};