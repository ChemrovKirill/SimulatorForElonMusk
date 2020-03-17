#pragma once
#include "Rectangle.h"
#include "Circle.h"

namespace gs {

	class Square : public Rectangle {
	public:
		Square(const Point&, const Point&);
		Circle circumscribedCircle() const;
		Circle inscribedCircle() const;
	};
}