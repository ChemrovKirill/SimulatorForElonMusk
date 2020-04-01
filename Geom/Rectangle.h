#pragma once

#include"Polygon.h"
#include<cmath>

class rectangle : public polygon {
private:
	std::vector<Point> GetStartPoints(const Point& a, const Point& b, double k) {
		std::vector<Point> v;
		Line diag (a, b);
		double d = diag.GetLength();
		double x = d / sqrt(1 + k * k);
		double y = k * x;
		Point p1, p2;

		double a_angle = diag.GetAngle() + (atan(k) / RAD);
		p1.x = a.x + x * cos(RAD * a_angle);
		p1.y = a.y + x * sin(RAD * a_angle);
		double b_angle = 90 - a_angle;
		p2.x = a.x + y * cos(RAD * b_angle);
		p2.y = a.y - y * sin(RAD * b_angle);
		
		v.push_back(a);
		v.push_back(p1);
		v.push_back(b);
		v.push_back(p2);
		return v;
	}
public:
	rectangle(const Point& a, const Point& b, double k) 
		: polygon(GetStartPoints(a, b, k)){}

	Point center() const { 
		std::vector<Point> v = GetVertices();
		return Point((v[0].x + v[2].x) / 2, (v[0].y + v[2].y) / 2); 
	}

	std::pair<Line, Line> diagonals() const  {
		return std::pair<Line, Line>(Line(vertices[0], vertices[2]), Line(vertices[1], vertices[3]));
	}
};