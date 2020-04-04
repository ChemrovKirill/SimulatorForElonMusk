#include"RigidBody.h"

#define RESTITUTION 0.4f

void RigidBody::CollisionReactionWithSurface(const Line& l, bool first_collision) {
	static Vector2f old_position{0,0};
	if (first_collision == true) {
		velocity = -velocity;
		velocity = rotate_to_angle(velocity, 2 * angle_between_2_vectors(velocity, normal_to_line(l))) * RESTITUTION;
		angle_velocity = 0;
		old_position = position;
	}
	position = old_position + normal_to_line(l) / 4;
}





