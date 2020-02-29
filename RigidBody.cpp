#include "RigidBody.h"

float RigidBody::GetMass() const { return mass; }
float RigidBody::GetMomentOfInertia() const { return moment_of_inertia; }
Vector2f RigidBody::GetMassPosition() const { return mass_position; }
Vector2f RigidBody::GetVelocuty() const { return velocity; }
Vector2f RigidBody::GetAcceleration() const { return acceleration; }
Vector2f RigidBody::GetAngleVelocity() const { return angle_velocity; }
Vector2f RigidBody::GetAngleAcceleration() const { return angle_acceleration; }

void RigidBody::SetMass(const float& new_mass) { mass = new_mass; }
void RigidBody::SetMomentOfInertia(const float& new_moment_of_inertia) { moment_of_inertia = new_moment_of_inertia; }
void RigidBody::SetMassPosition(const Vector2f& new_mass_position) { mass_position = new_mass_position; }
void RigidBody::SetVelocuty(const Vector2f& new_velocity) { velocity = new_velocity; }
void RigidBody::SetAcceleration(const Vector2f& new_acceleration) { acceleration = new_acceleration; }
void RigidBody::SetAngleVelocity(const Vector2f& new_angle_velocity) { angle_velocity = new_angle_velocity; }
void RigidBody::SetAngleAcceleration(const Vector2f& new_angle_acceleration) { angle_acceleration = new_angle_acceleration; }
