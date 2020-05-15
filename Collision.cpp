#include"RigidBody.h"

void  RigidBody::Collision(const Surface& s) {
	CollisionDetection(s);
	
}

void RigidBody::CollisionModelDraw(RenderWindow& window) {
	std::vector<Point> polygon_vertex;

	for (Point i : collision_vertex) {
		float fb;
		float x = GetWidth() * i.x;
		float y = GetHeight() * i.y;
		if (x >= 0 && y != 0) { fb = atan(y / x); }
		else if (x < 0) { fb = atan(y / x) - PI; }
		else { fb = 0; }
		float diag = sqrt(pow(GetWidth() * i.x, 2) + pow(GetHeight() * i.y, 2));

		polygon_vertex.push_back(Point(
			(GetPosition().x + cos(RAD * GetAngle() + fb) * diag),
			(GetPosition().y + sin(RAD * GetAngle() + fb) * diag))
		);
	}

	VertexArray collysion_model;

	collysion_model.setPrimitiveType(LinesStrip);
	for (int i = 0; i < collision_vertex.size(); ++i) {
		collysion_model.append(Vertex(Vector2f(polygon_vertex[i].x, polygon_vertex[i].y), Color::Blue));
	}
	collysion_model.append(Vertex(Vector2f(polygon_vertex[0].x, polygon_vertex[0].y), Color::Blue));
	window.draw(collysion_model);
}


void RigidBody::CollisionDetection(const Surface& s) {
	
	long mid_iter = s.Get_iter_0() + 2 * GetCenterPosition().x / s.Get_spacing();
	long start = mid_iter - (height + width) /(2 * s.Get_spacing());
	long end = mid_iter + (height + width) / (2 * s.Get_spacing());

	if (start - (height + width) / (2 * s.Get_spacing()) <= 0 || end + (height + width) / (2 * s.Get_spacing()) >= s.Get_VertexCount()) { start = end = mid_iter = 0; return; }

	std::vector<Point> polygon_vertex;

	for (Point i : collision_vertex) {
		float fb;
		float x = GetWidth() * i.x;
		float y = GetHeight() * i.y;
		if (x >= 0 && y != 0) { fb = atan(y / x); }
		else if (x < 0) { fb = atan(y / x) - PI; }
		else { fb = 0; }
		float diag = sqrt(pow(GetWidth() * i.x, 2) + pow(GetHeight() * i.y, 2));

		polygon_vertex.push_back(Point(
			GetPosition().x + cos(RAD * GetAngle() + fb) * diag,
			GetPosition().y + sin(RAD * GetAngle() + fb) * diag)
		);
	}

	polygon collision_polygon(polygon_vertex);

	int step = 2;
	static bool first_collision = false;
	bool collision_detected = false;

	for (Point i : polygon_vertex) {

		for (int ii = 0; ii < polygon_vertex.size(); ++ii) {
			int it_point = (s.Get_iter_0() / 2) * 2 + 2 * polygon_vertex[ii].x / s.Get_spacing();
			for(int small_step = -4; small_step < 3; ++small_step){

				Line surface_line(Point(s.GetVertex(it_point + small_step).position.x, s.GetVertex(it_point + small_step).position.y),
					Point(s.GetVertex(it_point + step+ small_step).position.x, s.GetVertex(it_point + step+ small_step).position.y));

				if (IntercectionWithSurface(i, surface_line, s)) {
					CollisionReactionWithSurface(surface_line, first_collision, i);
					first_collision = false;
					collision_detected = true;
				}
				else {
					NOCollisionReaction();
				}
			}
		}
	}	

	for (int i = (start / 2) * 2; i < end; i += step) {
		Point p(s.GetVertex(i).position.x, s.GetVertex(i).position.y);
		if (collision_polygon.containsPoint(p)) {
			for (Line ii : collision_polygon.GetLines()) {
				if (ii.IsOnLine(p)) { CollisionReactionWithSurface(ii, first_collision, p); }
			}

			first_collision = false;
			collision_detected = true;
		}
		else {
			NOCollisionReaction();
		}
	}

	if (collision_detected == false) {
		first_collision = true;
	}
	return;
}

bool RigidBody::IntercectionWithSurface(const Point& p, const Line& surface_line, const Surface& s) const {
	double an = -100;
	bool success_cast = false;
	int intersection = 0;

	while (success_cast == false) {
		an += 10;
		Line ray(p, an, 1);
				
		if (p.x == surface_line.GetFirstPoint().x && surface_line.GetFirstPoint().y == p.y) { return true; }
		if (surface_line.GetFirstPoint().y == surface_line.GetFirstPoint().x * ray.GetK() + ray.GetKb()) {}
		else { success_cast = true; }
	}

	Line ray(p, an, -1000);

	Point int_p(ray.intersectionPoint(surface_line));
	if (((int_p.x >= surface_line.GetFirstPoint().x && int_p.x >= surface_line.GetSecondPoint().x) ||
		(int_p.x <= surface_line.GetFirstPoint().x && int_p.x <= surface_line.GetSecondPoint().x)) &&
		((int_p.y >= surface_line.GetFirstPoint().y && int_p.y >= surface_line.GetSecondPoint().y) ||
		(int_p.y <= surface_line.GetFirstPoint().y && int_p.y <= surface_line.GetSecondPoint().y))) {}
	else if (ray.GetFirstPoint().y < int_p.y) {}
	else { ++intersection; }

	if (intersection % 2 == 1) { return	true; }
	else { return false; }
}





//////////////////Function overloading is for visualization purposes only///////////////////////////////
void RigidBody::CollisionDetection(const Surface& s, RenderWindow& window) {
	
	long mid_iter = s.Get_iter_0() + 2 * GetCenterPosition().x / s.Get_spacing();
	long start = mid_iter - (height + width) /(2 * s.Get_spacing());
	long end = mid_iter + (height + width) / (2 * s.Get_spacing());

	if (start - (height + width) / (2 * s.Get_spacing()) <= 0 || end + (height + width) / (2 * s.Get_spacing()) >= s.Get_VertexCount()) { start = end = mid_iter = 0; return; }
	
	std::vector<Point> polygon_vertex;

	for (Point i : collision_vertex) {
		float fb;
		float x = GetWidth() * i.x;
		float y = GetHeight() * i.y;
		if (x >= 0 && y != 0) { fb = atan(y / x); }
		else if (x < 0) { fb = atan(y / x) - PI; }
		else { fb = 0; }
		float diag = sqrt(pow(GetWidth() * i.x, 2) + pow(GetHeight() * i.y, 2));

		polygon_vertex.push_back(Point(
			GetPosition().x + cos(RAD * GetAngle() + fb) * diag,
			GetPosition().y + sin(RAD * GetAngle() + fb) * diag)
		);
	}

	polygon collision_polygon(polygon_vertex);

	int step = 2;
	static bool first_collision = false;
	bool collision_detected = false;

	for (Point i : polygon_vertex) {

		for (int ii = 0; ii < polygon_vertex.size(); ++ii) {
			int it_point = (s.Get_iter_0() / 2)* 2 + 2 * polygon_vertex[ii].x / s.Get_spacing();
			for(int small_step = -2; small_step < 1; ++small_step){

				Line surface_line(Point(s.GetVertex(it_point + small_step).position.x, s.GetVertex(it_point + small_step).position.y),
					Point(s.GetVertex(it_point + step+ small_step).position.x, s.GetVertex(it_point + step+ small_step).position.y));

				if (IntercectionWithSurface(i, surface_line, s, window)) {
					CollisionReactionWithSurface(surface_line, first_collision, i);

					CircleShape Cshape(10.f);
					Cshape.setFillColor(Color::Red);
					Cshape.setPosition({ static_cast<float>(i.x) - 5, static_cast<float>(i.y) - 5 });
					window.draw(Cshape);
					 
					first_collision = false;
					collision_detected = true;
				}
				else {
					NOCollisionReaction();
				}
			}
		}
	}	

	for (int i = (start / 2) * 2; i < end; i+=step) {
		Point p(s.GetVertex(i).position.x, s.GetVertex(i).position.y);
		if (collision_polygon.containsPoint(p)) {
			for (Line ii : collision_polygon.GetLines()) {
				if (ii.IsOnLine(p)) { CollisionReactionWithSurface(ii, first_collision, p); }
			}

			CircleShape Cshape(10.f);
			Cshape.setFillColor(Color::Red);
			Cshape.setPosition({ static_cast<float>(p.x) - 5, static_cast<float>(p.y) - 5 });
			window.draw(Cshape);

			first_collision = false;
			collision_detected = true;
		}
		else {
			NOCollisionReaction();
		}
	}

	if (collision_detected == false) {
		first_collision = true;
	}
	return;
}

bool RigidBody::IntercectionWithSurface(const Point& p, const Line& surface_line, const Surface& s, RenderWindow& window) const {
	double an = -100;
	bool success_cast = false;
	int intersection = 0;

	while (success_cast == false) {
		an += 10;
		Line ray(p, an, 1);
				
		if (p.x == surface_line.GetFirstPoint().x && surface_line.GetFirstPoint().y == p.y) { return true; }
		if (surface_line.GetFirstPoint().y == surface_line.GetFirstPoint().x * ray.GetK() + ray.GetKb()) {}
		else { success_cast = true; }
	}

	Line ray(p, an, -1000);

	surface_line.Print(window, Color::Red);
	ray.Print(window, Color::Blue);

	Point int_p(ray.intersectionPoint(surface_line));
	if (((int_p.x >= surface_line.GetFirstPoint().x && int_p.x >= surface_line.GetSecondPoint().x) ||
		(int_p.x <= surface_line.GetFirstPoint().x && int_p.x <= surface_line.GetSecondPoint().x)) &&
		((int_p.y >= surface_line.GetFirstPoint().y && int_p.y >= surface_line.GetSecondPoint().y) ||
		(int_p.y <= surface_line.GetFirstPoint().y && int_p.y <= surface_line.GetSecondPoint().y))) {}
	else if (ray.GetFirstPoint().y < int_p.y) {}
	else { ++intersection; }

	if (intersection % 2 == 1) { return	true; }
	else { return false; }
}


void  RigidBody::Collision(const Surface& s, RenderWindow& window) {

}
///////////////////////////////////////////////////////////////////////////////////////////////////////