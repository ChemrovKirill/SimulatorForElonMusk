#pragma once
#include "MathFunction.h"
#include "Object.h"
#include "Surface.h"
#include "Force.h"
#include <cmath>
#include <set>
#include <string>
#include "Geom/Geometric.h"

using namespace sf;

struct RigidBodyParameters {
	Vector2f position;
	float height;
	float width;
	float angle;
	
	float mass;
	Vector2f mass_position; //accepts values from 0 to 1
	float moment_of_inertia;

	Vector2f velocity;
	Vector2f acceleration;

	float angle_velocity;
	float angle_acceleration;

	std::vector<Point> collision_vertex;

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
protected:
	float mass;
	Vector2f mass_position; //accepts values from 0 to 1
	float moment_of_inertia; //Add an auto-calculation of the moment of inertia and push it into the arctangent and diag class!!!

	Vector2f velocity;
	Vector2f acceleration;

	float angle_velocity;
	float angle_acceleration;

	float diag = sqrt(pow(GetWidth() * GetMassPosition().x, 2) + pow(GetHeight() * GetMassPosition().y, 2));
	//Distance from the center of mass to the upper-left corner
	float b = atan((GetHeight() * GetMassPosition().y) / (GetWidth() * GetMassPosition().x));
	//the angle between the horizon and the segment connecting the upper-left corner and the center of mass

	VertexArray way;
	std::vector<Point> collision_vertex;

	std::map<String,Force> forces;
public:
	RigidBody(const String& f, const RigidBodyParameters& parameters);

	float GetMass() const;
	float GetMomentOfInertia() const;
	Vector2f GetMassPosition() const;
	Vector2f GetCenterPosition() const;
	Vector2f GetAbsMassPosition() const;

	Vector2f GetVelocity() const;
	Vector2f GetAcceleration() const;
	float GetAngleVelocity() const;
	float GetAngleAcceleration() const;
	Force GetForce(const std::string& name) const;

	void SetMass(const float& new_mass);
	void SetMomentOfInertia(const float& new_moment_of_inertia);
	void SetMassPosition(const Vector2f& new_mass_position);
	void SetVelocuty(const Vector2f& new_velocity);
	void SetAcceleration(const Vector2f& new_acceleration);
	void SetAngleVelocity(const float& new_angle_velocity);
	void SetAngleAcceleration(const float& new_angle_acceleration);

	void UpdatePosition(const float& dt);
	void AddForce(const std::string& name, const Force& new_force);
	void DeleteForce(const std::string& name);
	void ForceOn(const std::string& name);
	void ForceOff(const std::string& name);
	void UpdateForces();

	void DrawMassPosition(RenderWindow& window) const;
	void DrawBodyWay(RenderWindow& window);
	void DeleteBodyWay(RenderWindow& window);

	void DrawForce(RenderWindow& window, const Force& force) const;
	void DrawSpeed(RenderWindow& window) const;

	void Collision(const Surface& s);
	void Collision(const Surface& s, RenderWindow& window);
	void CollisionModelDraw(RenderWindow& window);
	void CollisionDetection(const Surface& s);
	void CollisionDetection(const Surface& s, RenderWindow& window);
private:
	bool IntercectionWithSurface(const Point& p, const Line& surface_line, const Surface& s) const;
	bool IntercectionWithSurface(const Point& p, const Line& surface_line, const Surface& s, RenderWindow& window) const;
	
	void CollisionReactionWithSurface(const Line& l, bool first_collision, const Point& p);

	void CollisionReaction(bool first_collision, Point force_point);
	void NOCollisionReaction();
};