#include "Ellipse.h"

using namespace gs;

Ellipse::Ellipse(const Point& f1, const Point& f2, const double& dist)
: focuses(f1, f2), sum_of_dist(dist) {
	c = sqrt((f2.x - f1.x) * (f2.x - f1.x) + (f2.y - f1.y)*(f2.y - f1.y))/2;
	a = sum_of_dist / 2;
	b = sqrt(a * a - c * c);
}

std::pair<Point, Point> Ellipse::GetFocuses() const {
	return focuses;
}

double Ellipse::Get_a() const { return a; }
double Ellipse::Get_b() const { return b; }
double Ellipse::eccentricity() const {
	return c/a;
}
Point Ellipse::center() const {
	Point c;
	c.x = (focuses.first.x + focuses.second.x) / 2;
	c.y = (focuses.first.y + focuses.second.y) / 2;
	return c;
}
double Ellipse::perimeter() const {
	return 4*(PI * a * b + (a-b)*(a-b))/(a+b);
}
double Ellipse::area() const {
	return PI*a*b;
}
bool Ellipse::operator==(const Shape& sh) const {
	const Ellipse& another = dynamic_cast<const Ellipse&>(sh);
	if ((abs(sum_of_dist - another.sum_of_dist)) < EPSILON) {
		if (focuses == another.focuses) {
			return true;
		}
	}
	return false;
}
bool Ellipse::isCongruentTo(const Shape& sh) const {
	const Ellipse& another = dynamic_cast<const Ellipse&>(sh);
	return another.a == a && another.b == b;
}
bool Ellipse::containsPoint(const Point& p) const {
	Line dist_1(p, focuses.first);
	Line dist_2(p, focuses.second);
	return dist_1.Length() + dist_2.Length() <= sum_of_dist;
}