#pragma once

#include"Rectangle.h"
#include"Circle.h"

class square : public rectangle {
public:
	square(const Point& p1, const Point& p2) : rectangle(p1, p2, 1) {}
	square(const square& s) : rectangle(s.GetVertices()[0], s.GetVertices()[2], 1) {}

	circle circumscribedCircle() const {
		return circle(center(), diagonals().first.GetLength() / 2);
	}
	circle inscribedCircle() const {
		Line l(center(), Point((vertices[0].x + vertices[1].x) / 2, (vertices[0].y + vertices[1].y) / 2));
		return circle(center(), l.GetLength());
	}
};