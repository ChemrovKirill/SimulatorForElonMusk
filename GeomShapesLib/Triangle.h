#pragma once
#include "Polygon.h"
#include "Circle.h"
#include "Line.h"

namespace gs {

	class Triangle : public Polygon {
	public:
		Triangle(const Point& p1, const Point& p2, const Point& p3);
		Circle circumscribedCircle();
		Circle inscribedCircle();
		Point centroid();
		Point orthocenter();
		Line EulerLine();
		Circle ninePointsCircle();
	};
}