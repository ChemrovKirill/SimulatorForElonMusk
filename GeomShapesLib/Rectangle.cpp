#include "Rectangle.h"

using namespace gs;

std::vector<Point> GetRectangleVertexes(const Point& p1, const Point& p3, const double k) {
	double a, b, d;
	Line diag(p1, p3);
	d = diag.Length();
	a = d / sqrt(1 + k * k);
	b = k*a;
	Point p2, p4;
	double a_angle = diag.Angle() + (RAD_TO_DEG * atan(b / a));
	p2.x = p1.x + a * cos(DEG_TO_RAD * a_angle);
	p2.y = p1.y + a * sin(DEG_TO_RAD * a_angle);
	double b_angle = 90 - a_angle;
	p4.x = p1.x + b * cos(DEG_TO_RAD * b_angle);
	p4.y = p1.y - b * sin(DEG_TO_RAD * b_angle);
	return { p1, p2, p3, p4 };
}

Rectangle::Rectangle(const Point& p1, const Point& p3, const double k) 
: Polygon(GetRectangleVertexes(p1, p3 ,k)){

}

Point Rectangle::center() const {
	Line diag_1(vertices[0], vertices[2]);
	Line diag_2(vertices[1], vertices[3]);
	return diag_1.IntersectionPoint(diag_2);
}

std::pair<Line, Line> Rectangle::diagonals() const {
	Line diag_1(vertices[0], vertices[2]);
	Line diag_2(vertices[1], vertices[3]);
	return { diag_1, diag_2 };
}