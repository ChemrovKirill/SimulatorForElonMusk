#include"RigidBody.h"

#define RESTITUTION 0.2f

void RigidBody::CollisionReactionWithSurface(const Line& l, bool first_collision, const Point& p) {
	static Vector2f old_position{ 0,0 };
	if (first_collision == true) {
		Vector2f collision_point(p.x - position.x, p.y - position.y);
		collision_point = rotate_to_angle(collision_point, GetAngle());
		collision_point = Vector2f(collision_point.x / GetWidth(), collision_point.y / GetHeight());

		Vector2f normal = normal_to_line(l);
		Vector2f collision_center_line = GetCenterPosition() - Vector2f(p.x, p.y);

		float deviation_angle = angle_between_2_vectors(normal, collision_center_line);

		Vector2f old_velocity = velocity;

		velocity = rotate_to_angle(velocity, deviation_angle);
		velocity = -velocity * sqal(velocity) * cos(deviation_angle) / sqal(velocity);
		velocity = rotate_to_angle(velocity, 2 * angle_between_2_vectors(velocity, collision_center_line)) * RESTITUTION;
		

		float other_velocity = sqal(old_velocity) * mod(sin(deviation_angle));

		int x = 1;
		if (angle_between_2_vectors(velocity, normal) > 0) { x = -1; }
		else { x = 1; }

		angle_velocity = (x * other_velocity * RESTITUTION) / (sqal(collision_center_line) * RAD);
		//if (other_velocity < 20) {
		//	angle_velocity = (sin(deviation_angle) * 100 * RESTITUTION) / (sqal(collision_center_line) * RAD);
		//}
		//angle_velocity += RESTITUTION * sqal(collision_center_line) * other_velocity * mass / moment_of_inertia;
		//std::cout << angle_velocity << " " << other_velocity << " " << sqal(collision_center_line) << std::endl;
		old_position = position;
		position = old_position + normal_to_line(l) / 4;
	}
	else {
	}

	if (angle_velocity < 4 && angle_velocity > -4) { angle_velocity = 0; }
	else if (angle_velocity > 0) { angle_velocity += 2; }
	else if (angle_velocity < 0) { angle_velocity -= 2; }
 		 
	position += normal_to_line(l) / 4;
}

/*void RigidBody::CollisionReactionWithSurface(const Line& l, bool first_collision) {
	static Vector2f old_position{0,0};
	if (first_collision == true) {
		velocity = -velocity;
		velocity = rotate_to_angle(velocity, 2 * angle_between_2_vectors(velocity, normal_to_line(l))) * RESTITUTION;
		angle_velocity = 0;
		old_position = position;
	}
	position = old_position + normal_to_line(l) / 4;
}*/






void RigidBody::CollisionReaction(bool first_collision, Point force_point) {
	if (first_collision == true) {
		velocity.x = 0;
		velocity.y = 0;
		angle_velocity = 0;

		//position.y -= 1;
	}
	else {
		if (acceleration.y >= 0) {
			velocity.x = 0;
			velocity.y = 0;
			angle_velocity = 0;
		}


	}
	static int i = 0;
	++i;
	//std::cout << "Collision! " << i << std::endl;
}

void RigidBody::NOCollisionReaction() {

}