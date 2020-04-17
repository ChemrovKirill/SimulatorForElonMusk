#include "Force.h"

using namespace sf;

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
Force Force::operator = (const Force& f) {
	exist = f.exist;
	is_force_field = f.is_force_field;
	force = f.force;
	force_vector = f.force_vector;
	force_point = f.force_point;
	return f;
}
