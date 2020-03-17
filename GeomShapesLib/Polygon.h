#pragma once
#include "Shape.h"
#include "Line.h"
#include "Point.h"
#include "vector"

namespace gs {

	class Polygon : public Shape {
	protected:
		std::vector<Point> vertices;
		std::vector<Line> sides;
	public:
		Polygon(const std::vector<Point>&);
		Polygon(const std::vector<Line>&);

		std::vector<Point> getVertices() const;

		size_t verticesCount() const;

		bool isConvex() const;
		bool isPolygon() const;

		double perimeter() const;
		double area()const;
		bool operator==(const Shape&) const;
		bool isCongruentTo(const Shape&) const;
		bool containsPoint(const Point&) const;
	};
}