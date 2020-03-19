#pragma once
#include "Point.h"
namespace gs {

	class Shape {
	private:

	public:
		virtual ~Shape() {}
		virtual double perimeter() const = 0;
		virtual double area()const = 0;
		virtual bool operator==(const Shape&) const = 0;
		virtual bool isCongruentTo(const Shape&) const = 0;
		virtual bool containsPoint(const Point&) const = 0;
	};
}