#include "Square.h"

using namespace gs;

Square::Square(const Point& p1, const Point& p3)
	: Rectangle(p1, p3, 1) {}

Circle Square::circumscribedCircle() const {
	return Circle(center(), sides[0].Length()/sqrt(2));
}
Circle Square::inscribedCircle() const {
	return Circle(center(), sides[0].Length()/2);
}