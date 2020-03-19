#pragma once
#include "Point.h"
#include "cmath"

namespace gs {

	class Line {
	private:
		Point point_1, point_2;
		double length;
		double angle; //degrees
	public:
		Line(const Point&, const Point&);

		Line(const Point&, const double&, const double&);

		Point point(const size_t&) const;

		double Length() const { return length; }
		double Angle() const { return angle; }

		Point mid() const;

		Point IntersectionPoint(const Line&) const;

		bool containsPoint(const Point&) const;
		bool isPointInside(const Point&) const;
		bool PointOnLine(const Point&) const;

		bool Intersects(const Line&) const;
		bool IntersectsInside(const Line&) const;

		bool isCongruentTo(const Line&) const;

		bool operator == (const Line&) const;
		bool operator != (const Line&) const;
	};
}