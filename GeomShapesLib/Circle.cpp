#include "Circle.h"

using namespace gs;

Circle::Circle(const Point& c, const double& r)
	: Ellipse(c, c, 2*r) {}

double Circle::radius() { return a; }
