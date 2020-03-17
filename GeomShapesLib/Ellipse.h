#pragma once
#include "Shape.h"
#include "Point.h"
#include "Line.h"

namespace gs {

	class Ellipse : public Shape {
	protected:
		std::pair<Point, Point> focuses;
		double sum_of_dist;
		double a, b, c;
	public:
		Ellipse(const Point&, const Point&, const double& dist);
		std::pair<Point, Point> GetFocuses() const;
		double Get_a() const;
		double Get_b() const;
		double eccentricity() const;
		Point center() const;
		double perimeter() const;
		double area()const;
		bool operator==(const Shape&) const;
		bool isCongruentTo(const Shape&) const;
		bool containsPoint(const Point&) const;
	};

}