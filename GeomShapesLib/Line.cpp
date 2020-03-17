#include "Line.h"

using namespace gs;

Line::Line(const Point& p1, const Point& p2)
	: point_1(p1), point_2(p2) {
	length = sqrt((point_2.x - point_1.x) * (point_2.x - point_1.x) +
		(point_2.y - point_1.y) * (point_2.y - point_1.y));
	angle = RAD_TO_DEG * atan((point_2.y - point_1.y) / (point_2.x - point_1.x));
}

Line::Line(const Point& p1, const double& a, const double& l)
	: point_1(p1), angle(a), length(l) {
	point_2.x = point_1.x + length * cos(DEG_TO_RAD * angle);
	point_2.y = point_1.y + length * sin(DEG_TO_RAD * angle);
}

Point Line::point(const size_t& i) const {
	if (i == 1) {
		return point_1;
	}
	else if (i == 2) {
		return point_2;
	}
}

Point Line::mid() const {
	Point mid;
	mid.x = (point(1).x + point(2).x) / 2;
	mid.y = (point(1).y + point(2).y) / 2;
	return mid;
}

Point Line::IntersectionPoint(const Line& l) const {
	Point p;
	double tg_1 = tan(DEG_TO_RAD * angle);
	double tg_2 = tan(DEG_TO_RAD * l.angle);
	double x_1 = point_1.x;
	double y_1 = point_1.y;
	double x_2 = l.point_1.x;
	double y_2 = l.point_1.y;
	p.x = (x_2 * tg_2 - x_1 * tg_1 - y_2 + y_1) / (tg_2 - tg_1);
	p.y = y_1 + (p.x - x_1) * tg_1;
	return p;
}

bool Line::containsPoint(const Point& p) const {
	if (PointOnLine(p)) {
		return (p.x >= point_1.x&& p.x <= point_2.x) || (p.x <= point_1.x && p.x >= point_2.x) ||
			(p.y >= point_1.y&& p.y <= point_2.y) || (p.y <= point_1.y && p.y >= point_2.y);
	}
	else {
		return false;
	}
}

bool Line::PointOnLine(const Point& p) const {
	double tg = tan(DEG_TO_RAD * angle);
	double x_1 = point_1.x;
	double y_1 = point_1.y;
	if (abs(angle - 90) < EPSILON) {
		if (abs(p.x - x_1) < EPSILON) {
			return true;
		}
	}
	else if (abs((p.y - y_1) - ((p.x - x_1) * tg)) < EPSILON) {
		return true;
	}
	return false;
}

bool Line::isPointInside(const Point& p) const {
	if (PointOnLine(p)) {
		return (p.x > point_1.x && p.x < point_2.x) || (p.x < point_1.x && p.x > point_2.x) ||
			(p.y > point_1.y&& p.y < point_2.y) || (p.y < point_1.y && p.y > point_2.y);
	}
	else
		return false;
}

bool Line::Intersects(const Line& l) const {
	if (abs(angle - l.angle) < EPSILON || abs(angle - l.angle + 180) < EPSILON) {
		return 0;
	}
	return containsPoint(IntersectionPoint(l));
}

bool Line::IntersectsInside(const Line& l) const {
	if (abs(angle - l.angle) < EPSILON || abs(angle - l.angle + 180) < EPSILON) {
		return 0;
	}
	return isPointInside(IntersectionPoint(l));
}

bool Line::isCongruentTo(const Line& l) const {
	return length == l.length;
}

bool Line::operator == (const Line& l) const {
	return l.point_1 == point_1 && l.point_2 == point_2;
}
bool Line::operator != (const Line& l) const {
	return l.point_1 != point_1 || l.point_2 != point_2;
}