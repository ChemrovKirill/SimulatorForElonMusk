#pragma once

#include "Object.h"
#include "Surface.h"
#include <cmath>
#include <set>
#include <string>

using namespace sf;

struct RigidBodyParameters {
	Vector2f position;
	float height;
	float width;
	float angle;
	
	float mass;
	Vector2f mass_position; //ïðèíèìàåò çíà÷åíèÿ îò 0 äî 1
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
	Vector2f force_vector; //åñëè ñèëà ñîçäàåò ïîëå, òî âåêòîð - íàïðÿæåííîñòü ïîëÿ, èíà÷å
						   //åäèíè÷íûé âåêòîð, íàïðàâëåííûé îòíîñèòåëüíî îðèåíòàöèè êîðîáëÿ: 
						   //(0,-1) - ââåðõ îòíîñèòåëüíî íîñà, (0,1) - âíèç, (1,0) - âïðàâî, (-1,0) - âëåâî
	Vector2f force_point;  //òî÷êà ïðèëîæåíèÿ ñèëû, ïðèíèìàåò çíà÷åíèÿ îò 0 äî 1

	Force();
	Force(bool field, float new_force, Vector2f start_vector, Vector2f start_force_point);
	Force operator = (const Force&);
};

class RigidBody : public Object {
protected:
	float mass;
	Vector2f mass_position; //ïðèíèìàåò çíà÷åíèÿ îò 0 äî 1
	float moment_of_inertia; //Äîáàâèòü àâòîðàññ÷åò ìîìåíòà èíåðöèè è çàïèõàòü â êëàññ àðêòàíãåíñ è diag!!!

	Vector2f velocity;
	Vector2f acceleration;

	float angle_velocity;
	float angle_acceleration;

	float diag = sqrt(pow(GetWidth() * GetMassPosition().x, 2) + pow(GetHeight() * GetMassPosition().y, 2));
	//Ðàññòîÿíèå îò öåíòðà ìàññ äî ëåâîãî âåðõíåãî óãëà
	float b = atan((GetHeight() * GetMassPosition().y) / (GetWidth() * GetMassPosition().x));
	//óãîë ìåæäó ãîðèçîíòîì è îòðåçêîì, ñîåäèíÿþùèì ëåâûé âåðõíèé óãîë è öåíòð ìàññ

	VertexArray way;

	std::map<String,Force> forces;
public:
	RigidBody(const String& f, const RigidBodyParameters& parameters);

	float GetMass() const;
	float GetMomentOfInertia() const;
	Vector2f GetMassPosition() const;
	Vector2f GetVelocuty() const;
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

	virtual void UpdatePosition(const float& dt);
	void AddForce(const Force& new_force, const std::string& name);
	void ForceOn(const std::string& name);
	void ForceOff(const std::string& name);
	void UpdateForces();

	void DrawMassPosition(RenderWindow& window) const;
	void DrawBodyWay(RenderWindow& window);
	void DeleteBodyWay(RenderWindow& window);
	void DrawForce(RenderWindow& window, const Force& force);
	void DrawSpeed(RenderWindow& window);
	void CollisionDetection(const Surface&);
};