#include "Point.h"

using namespace gs;

bool Point::operator == (const Point& p) const {
	return (abs(p.x - x) < EPSILON) && (abs(p.y - y) < EPSILON);
}
bool Point::operator != (const Point& p) const {
	return !((*this) == p);
}

std::ostream& operator << (std::ostream& os, const Point& p) {
	os << "(" << p.x << ", " << p.y << ")";
	return os;
}