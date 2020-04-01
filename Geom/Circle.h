#pragma once

#include"Ellipse.h"

class circle : public ellipse {
public:
	circle(Point a, double r) : ellipse(a, a, 2 * r) {}
	circle(const circle& c) : ellipse(c.focuses().first, c.focuses().first, c.GetDist() / 2) {}

	double radius() const { return GetDist() / 2; }
};