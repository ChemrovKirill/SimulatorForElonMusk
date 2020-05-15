#pragma once
#include "RigidBody.h"
							   //													   ^
class Engine : public Object { //force_vector calculated from the original angle: ---- | ---- - 0 grad, ---- -> ---- - 90 grad
private:
	Vector2f relative_position;
	Vector2f engine_vector;
	Force force;
	bool on;

	float thrust; //from 0 (0%) to 1 (100%) of force.force
	float thrust_angle; //from -1 (-100%) to 1 (100%) of max_thrust_angle
	float max_thrust_angle; //the angle at which the engine can deviate

	String f_sound = "engine.wav";
	SoundBuffer buffer;
	Sound sound;
public:
	Engine();
	Engine(const Object& object, const Vector2f& start_rel_pos, const Force& start_force, const float& start_max_thrust_angle);
	Engine(const Engine& e);

	Force GetForce() const;
	Vector2f GetRelPos() const;
	float GetThrust() const;
	float GetThrustAngle() const;
	float GetMaxThrustAngle() const;
	Vector2f GetEngineVector() const;

	void SetRelPos(const Vector2f& new_relative_position);
	void SetThrust(const float& new_thrust);
	void SetThrustAngle(const float& new_thrust_angle);
	void SetMaxThrustAngle(const float& new_max_thrust_angle);
	void SetEngineVector(const Vector2f& new_engine_vector);

	bool If_on() const;
	void SetOn();
	void SetOff();

	Engine operator = (const Engine&);
};
