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
	force_point(start_force_point), exist(false) {}
Force::Force(const Force& f) {
	exist = f.exist;
	is_force_field = f.is_force_field;
	force = f.force;
	force_point = f.force_point;
	force_vector = f.force_vector;
}



RigidBody::RigidBody(const String& f, const RigidBodyParameters& parameters)
	: Object(f, parameters.position, parameters.width, parameters.height, parameters.angle),
	mass(parameters.mass), moment_of_inertia(parameters.moment_of_inertia), mass_position(parameters.mass_position),
	velocity(parameters.velocity), acceleration(parameters.acceleration), angle_velocity(parameters.angle_velocity),
	angle_acceleration(parameters.angle_acceleration) {
	diag = sqrt(pow(GetWidth() * GetMassPosition().x, 2) + pow(GetHeight() * GetMassPosition().y, 2));
	if (GetWidth() * GetMassPosition().x != 0) {
		b = atan((GetHeight() * GetMassPosition().y) / (GetWidth() * GetMassPosition().x));
	}
	else { b = 0; }
}

float RigidBody::GetMass() const { return mass; }
float RigidBody::GetMomentOfInertia() const { return moment_of_inertia; }
Vector2f RigidBody::GetMassPosition() const { return mass_position; }
Vector2f RigidBody::GetVelocuty() const { return velocity; }
Vector2f RigidBody::GetAcceleration() const { return acceleration; }
float RigidBody::GetAngleVelocity() const { return angle_velocity; }
float RigidBody::GetAngleAcceleration() const { return angle_acceleration; }
Force RigidBody::GetForce(const std::string& name) const { return forces.at(name); }

void RigidBody::SetMass(const float& new_mass) { mass = new_mass; }
void RigidBody::SetMomentOfInertia(const float& new_moment_of_inertia) { moment_of_inertia = new_moment_of_inertia; }
void RigidBody::SetMassPosition(const Vector2f& new_mass_position) { mass_position = new_mass_position; }
void RigidBody::SetVelocuty(const Vector2f& new_velocity) { velocity = new_velocity; }
void RigidBody::SetAcceleration(const Vector2f& new_acceleration) { acceleration = new_acceleration; }
void RigidBody::SetAngleVelocity(const float& new_angle_velocity) { angle_velocity = new_angle_velocity; }
void RigidBody::SetAngleAcceleration(const float& new_angle_acceleration) { angle_acceleration = new_angle_acceleration; }

Vector2f RigidBody::GetAbsMassPosition() const {
	return { position.x + mass_position.x * width, position.y - mass_position.y * height };
}

void RigidBody::UpdatePosition(const float& dt) {
	Vector2f new_position;
	float new_angle;

	new_position.x = GetPosition().x + velocity.x * dt -
		RAD * angle_velocity * diag * dt * cos(RAD * GetAngle() + b + PI / 2);
	new_position.y = GetPosition().y + velocity.y * dt -
		RAD * angle_velocity * diag * dt * sin(RAD * GetAngle() + b + PI / 2);

	new_angle = GetAngle() + angle_velocity * dt;

	SetVelocuty(Vector2f(velocity.x + acceleration.x * dt, velocity.y + acceleration.y * dt));
	SetAngleVelocity(angle_velocity + angle_acceleration * dt);

	SetPosition(new_position, new_angle);
	UpdateForces();
}

void RigidBody::AddForce(const std::string& name, const Force& new_force) {
	forces[name] = new_force;
}

void RigidBody::ForceOn(const std::string& name) {
	forces[name].exist = true;
}
void RigidBody::ForceOff(const std::string& name) {
	forces[name].exist = false;
}

void RigidBody::UpdateForces() {
	Vector2f new_acceleration(0, 0);
	float new_angle_accelaration = 0;

	for (auto i : forces) {
		if (i.second.exist == true) {
			if (i.second.is_force_field == true) {
				new_acceleration.x += i.second.force_vector.x;
				new_acceleration.y += i.second.force_vector.y;
			}
			else {
				float Fx = i.second.force * i.second.force_vector.x;
				float Fy = i.second.force * i.second.force_vector.y;

				new_acceleration.x += (Fx * cos(RAD * GetAngle()) - Fy * sin(RAD * GetAngle())) / mass;
				new_acceleration.y += (Fx * sin(RAD * GetAngle()) + Fy * cos(RAD * GetAngle())) / mass;

				new_angle_accelaration += (Fx * GetHeight() * (mass_position.y - i.second.force_point.y)) / moment_of_inertia;
				new_angle_accelaration -= (Fy * GetWidth() * (mass_position.x - i.second.force_point.x)) / moment_of_inertia;
			}
		}
	}

	SetAcceleration(new_acceleration);
	SetAngleAcceleration(new_angle_accelaration);
}

void RigidBody::DrawMassPosition(RenderWindow& window) const {
	CircleShape shape(10.f);
	shape.setFillColor(Color::Red);
	shape.setPosition(
		GetPosition().x + diag * cos(RAD * GetAngle() + b) - 10,
		GetPosition().y + diag * sin(RAD * GetAngle() + b) - 10
	);
	window.draw(shape);
}

void RigidBody::DrawBodyWay(RenderWindow& window) {
	way.setPrimitiveType(LinesStrip);
	way.append(Vertex(Vector2f(GetPosition().x + diag * cos(RAD * GetAngle() + b),
		GetPosition().y + diag * sin(RAD * GetAngle() + b)),
		Color::Red
	));
	window.draw(way);
}

void RigidBody::DeleteBodyWay(RenderWindow& window) {
	way.clear();
}

void RigidBody::DrawForce(RenderWindow& window, const Force& force) const {
	if (force.exist == true) {
		VertexArray force_line;
		force_line.setPrimitiveType(Lines);

		if (force.is_force_field == false) {
			float diag_force = sqrt(pow(GetWidth() * force.force_point.x, 2) + pow(GetHeight() * force.force_point.y, 2));
			float diag_force_end = sqrt(
				pow(GetWidth() * force.force_point.x + force.force * force.force_vector.x, 2) +
				pow(GetHeight() * force.force_point.y + force.force * force.force_vector.y, 2)
			);
			float x, y;

			float fb;
			x = GetWidth() * force.force_point.x;
			y = GetHeight()* force.force_point.y;

			if (x >= 0 && y != 0) { fb = atan(y / x); }
			else if (x < 0) { fb = atan(y / x) - PI; }
			else { fb = 0; }

			float feb;
			x = GetWidth() * force.force_point.x + force.force * force.force_vector.x;
			y = GetHeight()* force.force_point.y + force.force * force.force_vector.y;

			if (x >= 0 && y != 0) { feb = atan(y / x); }
			else if (x < 0) { feb = atan(y / x) - PI; }
			else { feb = 0; }

			force_line.append(Vertex(Vector2f(
				GetPosition().x + cos(RAD * GetAngle() + fb) * diag_force,
				GetPosition().y + sin(RAD * GetAngle() + fb) * diag_force),
				Color::Green
			));
			force_line.append(Vertex(Vector2f(
				GetPosition().x + cos(RAD * GetAngle() + feb) * diag_force_end,
				GetPosition().y + sin(RAD * GetAngle() + feb) * diag_force_end),
				Color::Green
			));
		}
		else {
			force_line.append(Vertex(Vector2f(
				GetPosition().x + cos(RAD * GetAngle() + b) * diag,
				GetPosition().y + sin(RAD * GetAngle() + b) * diag),
				Color::Green
			));
			force_line.append(Vertex(Vector2f(
				GetPosition().x + cos(RAD * GetAngle() + b) * diag + force.force_vector.x * mass,
				GetPosition().y + sin(RAD * GetAngle() + b) * diag + force.force_vector.y * mass),
				Color::Green
			));
		}
		window.draw(force_line);
	}
}


void RigidBody::DrawSpeed(RenderWindow& window) const {
	VertexArray speed_line;
	speed_line.setPrimitiveType(Lines);

	speed_line.append(Vertex(Vector2f(
		GetPosition().x + cos(RAD * GetAngle() + b) * diag,
		GetPosition().y + sin(RAD * GetAngle() + b) * diag),
		Color::Blue
	));
	speed_line.append(Vertex(Vector2f(
		GetPosition().x + cos(RAD * GetAngle() + b) * diag + velocity.x * mass,
		GetPosition().y + sin(RAD * GetAngle() + b) * diag + velocity.y * mass),
		Color::Blue
	));
	window.draw(speed_line);
}

bool RigidBody::CollisionDetection(const Surface& s) {
	int mid_iter = s.Get_iter_0() + 2*position.x/s.Get_spacing();
	//std::cout << s.Get_iter_0() << " " << s.GetVertex(mid_iter).position.x << std::endl;
	int start = mid_iter - (width + height) / s.Get_spacing();
	if (start < 0) {
		start = 0;
	}
	int end = mid_iter + (width + height) / s.Get_spacing();
	if (end > s.Get_VertexCount()) {
		end = s.Get_VertexCount();
	}
	//std::cout << start <<" " << mid_iter << " " << end << std::endl;
	for (int i = start; i < end; ++i) {
		//std::cout << s.GetVertex(i).position.x << std::endl;
		if (PointInside(s.GetVertex(i).position)) {
			//std::cout << "Collision" << std::endl;
			return true;
		}
	}
	return false;
}

Force Force::operator = (const Force& f) {
	exist = f.exist;
	is_force_field = f.is_force_field;
	force = f.force;
	force_vector = f.force_vector;
	force_point = f.force_point;
	return f;
}
