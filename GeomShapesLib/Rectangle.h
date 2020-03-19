#pragma once

#include "Polygon.h"
namespace gs {

	class Rectangle : public Polygon {
	private:
	public:
		Rectangle(const Point&, const Point&, const double);
		Point center() const;
		std::pair<Line, Line> diagonals() const;
	};
}