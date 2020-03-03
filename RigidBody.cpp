#include "RigidBody.h"

RigidBodyParameters::RigidBodyParameters()
	: position(Vector2f(0, 0)), width(0), height(0), angle(0), mass(0),
	moment_of_inertia(0), mass_position(Vector2f(0, 0)),
	velocity(Vector2f(0, 0)), acceleration(Vector2f(0, 0)), angle_velocity(0),
	angle_acceleration(0) {}

RigidBodyParameters::RigidBodyParameters(const Vector2f new_position,
	const float& w, const float& h, const float& start_angle,
	const float& start_mass, const float& start_moment_of_inertia,
	const Vector2f& start_mass_position)
	: position(new_position), width(w), height(h), angle(start_angle), mass(start_mass),
	moment_of_inertia(start_moment_of_inertia), mass_position(start_mass_position),
	velocity(Vector2f(0, 0)), acceleration(Vector2f(0, 0)), angle_velocity(0),
	angle_acceleration(0) {}

RigidBodyParameters::RigidBodyParameters(const Vector2f new_position,
	const float& w, const float& h, const float& start_angle,
	const float& start_mass, const float& start_moment_of_inertia,
	const Vector2f& start_mass_position, const Vector2f& start_velocity,
	const Vector2f& start_acceleration, const float& start_angle_velocity,
	const float& start_angle_acceleration) 
	: position(new_position), width(w), height(h), angle(start_angle), mass(start_mass),
	moment_of_inertia(start_moment_of_inertia), mass_position(start_mass_position),
	velocity(start_velocity), acceleration(start_acceleration), angle_velocity(start_angle_velocity),
	angle_acceleration(start_angle_acceleration) {}



Force::Force() : is_force_field(false), force(0), force_vector(Vector2f(0, 0)),
	force_point(Vector2f(0, 0)), exist(false) {};
Force::Force(bool field, float new_force, Vector2f start_vector, Vector2f start_force_point)
	: is_force_field(field), force(new_force), force_vector(start_vector), 
	force_point(start_force_point), exist(true) {}



RigidBody::RigidBody(const String& f, const RigidBodyParameters& parameters) 
	: Object(f, parameters.position, parameters.width, parameters.height, parameters.angle),
	mass(parameters.mass), moment_of_inertia(parameters.moment_of_inertia), mass_position(parameters.mass_position),
	velocity(parameters.velocity), acceleration(parameters.acceleration), angle_velocity(parameters.angle_velocity),
	angle_acceleration(parameters.angle_acceleration) {}

float RigidBody::GetMass() const { return mass; }
float RigidBody::GetMomentOfInertia() const { return moment_of_inertia; }
Vector2f RigidBody::GetMassPosition() const { return mass_position; }
Vector2f RigidBody::GetVelocuty() const { return velocity; }
Vector2f RigidBody::GetAcceleration() const { return acceleration; }
float RigidBody::GetAngleVelocity() const { return angle_velocity; }
float RigidBody::GetAngleAcceleration() const { return angle_acceleration; }

void RigidBody::SetMass(const float& new_mass) { mass = new_mass; }
void RigidBody::SetMomentOfInertia(const float& new_moment_of_inertia) { moment_of_inertia = new_moment_of_inertia; }
void RigidBody::SetMassPosition(const Vector2f& new_mass_position) { mass_position = new_mass_position; }
void RigidBody::SetVelocuty(const Vector2f& new_velocity) { velocity = new_velocity; }
void RigidBody::SetAcceleration(const Vector2f& new_acceleration) { acceleration = new_acceleration; }
void RigidBody::SetAngleVelocity(const float& new_angle_velocity) { angle_velocity = new_angle_velocity; }
void RigidBody::SetAngleAcceleration(const float& new_angle_acceleration) { angle_acceleration = new_angle_acceleration; }

void RigidBody::UpdatePosition(const float& dt) {
	Vector2f new_position;
	float new_angle;
	float diag = sqrt(pow(GetWidth() * GetMassPosition().x, 2) + pow(GetHeight() * GetMassPosition().y, 2));
	//–ассто€ние от центра масс до левого верхнего угла
	float b = atan(GetHeight() / GetWidth());

	new_position.x = GetPosition().x + velocity.x * dt -
		RAD * angle_velocity * diag * dt * cos(RAD * GetAngle() + b + PI / 2);
	new_position.y = GetPosition().y + velocity.y * dt -
		RAD * angle_velocity * diag * dt * sin(RAD * GetAngle() + b + PI / 2);

	new_angle = GetAngle() + angle_velocity * dt;

	SetVelocuty(Vector2f(velocity.x + acceleration.x * dt, velocity.y + acceleration.y * dt));
	SetAngleVelocity(angle_velocity + angle_acceleration * dt);

	SetObjectPosition(new_position, new_angle);
	UpdateForces();
}

void RigidBody::AddForce(const Force& new_force, int num) { 
	forces[num] = new_force; 
}
void RigidBody::ForceOn(int num) {
	forces[num].exist = true; 
}
void RigidBody::ForceOff(int num) {
	forces[num].exist = false; 
}

void RigidBody::UpdateForces() {
	Vector2f new_acceleration(0,0);
	float new_angle_accelaration = 0;

	for (auto i : forces) {
		if (i.exist == true) {
			if (i.is_force_field == true) {
				new_acceleration.x += i.force_vector.x;
				new_acceleration.y += i.force_vector.y;
			}
			else {
				float Fx = i.force * i.force_vector.x;
				float Fy = i.force * i.force_vector.y;

				new_acceleration.x += (Fx * cos(RAD * GetAngle()) - Fy * sin(RAD * GetAngle())) / mass;
				new_acceleration.y += (Fx * sin(RAD * GetAngle()) + Fy * cos(RAD * GetAngle())) / mass;

				new_angle_accelaration -= (Fx * GetHeight() * (mass_position.y - i.force_point.y)) / moment_of_inertia;
				new_angle_accelaration -= (Fy * GetWidth() * (mass_position.x - i.force_point.x)) / moment_of_inertia;
			}
		}
	}

	SetAcceleration(new_acceleration);
	SetAngleAcceleration(new_angle_accelaration);
}
