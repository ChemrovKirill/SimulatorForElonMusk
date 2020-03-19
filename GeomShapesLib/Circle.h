#pragma once
#include "Ellipse.h"
#include "Point.h"

namespace gs {

	class Circle : public Ellipse {
	public:
		Circle(const Point& c, const double& r);
		double radius();
	};
}
