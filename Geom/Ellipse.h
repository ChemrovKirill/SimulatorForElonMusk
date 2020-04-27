#pragma once

#include"shape.h"

class ellipse : public shape {
protected:
	Point f1, f2;
	double dist, a, b, c;
public:
	ellipse(Point new_a, Point new_b, double new_d) : f1(new_a), f2(new_b), dist(new_d) {
		c = sqrt((f2.x - f1.x) * (f2.x - f1.x) + (f2.y - f1.y) * (f2.y - f1.y)) / 2;
		a = dist / 2;
		b = sqrt(a * a - c * c);
	}
	ellipse(const ellipse& e) : f1(e.focuses().first), f2(e.focuses().second), dist(e.GetDist()),
		a(e.GetA()), b(e.GetB()), c(e.GetC()) {}
	
	double GetDist() const { return dist; }
	double GetA() const { return a; }
	double GetB() const { return b; }
	double GetC() const { return c; }
	std::pair<Point, Point> focuses() const { return std::pair<Point, Point>(f1, f2); }

	double eccentricity() { return c / a; }
	Point center() { return Point((f1.x + f2.x) / 2, (f1.y + f2.y) / 2); }

	double perimeter() const { return (4 * (PI * a * b + pow(a - b, 2)) / (a + b)); }
	double area() const { return PI * a * b; }
	bool operator==(const shape& shape) const {
		const ellipse& another = dynamic_cast<const ellipse&>(shape);
		if ((f1 == another.focuses().first && f2 == another.focuses().second && dist == another.GetDist()) ||
			(f1 == another.focuses().second && f2 == another.focuses().first && dist == another.GetDist()))
		{ return true; }
		else { return false; }
	}
	bool isCongruentTo(const shape& shape) const {
		const ellipse& another = dynamic_cast<const ellipse&>(shape);
		if (a == another.GetA() && b == another.GetB() && c == another.GetC()) { return true; }
		else { return false; }
	}
	bool containsPoint(const Point& p) const {
		Line a(p, f1), b(p, f2);
		if (a.GetLength() + b.GetLength() <= dist) { return true; }
		else { return false; }
	}

	void Print() const {
		HWND hwnd = GetConsoleWindow();
		HDC hdc = GetDC(hwnd);

		Point mid((f1.x + f2.x) / 2, (f1.y + f2.y) / 2);

		for (double angle = 0; angle < 360; angle+=0.1) {
			SetPixel(hdc, mid.x + a * cos(angle), mid.y + b * sin(angle), RGB(255, 255, 255));
		}
	}
};
