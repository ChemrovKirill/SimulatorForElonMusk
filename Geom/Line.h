#pragma once

#include"Point.h"
#include<cmath>

#define EPSILON 40	

class Line {
private:
	Point a, b;
	double angle; //в градусах относительно горизонтали
	double length;
	double k, kb;
public:
	Line(const Point& new_a,const Point& new_b) 
		: a(new_a), b(new_b), angle(atan((b.y - a.y) / (b.x - a.x)) / RAD), 
		length(sqrt(pow(a.x - b.x, 2) + pow(a.y - b.y, 2))) {
		k = tan(RAD * angle);
		kb = a.y - k * a.x;
	}
	Line(const Point& new_a, double new_angle, double new_length)
		: a(new_a), angle(new_angle), length(new_length),
		b(a.x + new_length * cos(RAD* new_angle), a.y + new_length * sin(RAD * new_angle)) {
		while (angle >  90) { angle -= 180; }
		while (angle < -90) { angle += 180; }
		k = tan(RAD * angle);
		kb = a.y - k * a.x;
	}
	Line(const Line& l) 
		: a(l.GetFirstPoint()), b(l.GetSecondPoint()), angle(l.GetAngle()), length(l.GetLength()),
		k(l.GetK()), kb(l.GetKb()) {}
	Line operator = (const Line& l) {
		a = l.GetFirstPoint();
		b = l.GetFirstPoint();
		angle = l.GetAngle();
		length = l.GetLength();
		k = l.GetK();
		kb = l.GetKb();
		return l;
	}

	Point GetFirstPoint() const { return a; }
	Point GetSecondPoint() const { return b; }
	double GetAngle() const { return angle; }
	double GetLength() const { return length; }
	double GetK() const { return k; }
	double GetKb() const { return kb; }
	
	bool operator == (const Line& l2) const {
		if (GetFirstPoint() == l2.GetFirstPoint() && GetSecondPoint() == l2.GetSecondPoint()) { return true; }
		else if (GetFirstPoint() == l2.GetSecondPoint() && GetSecondPoint() == l2.GetFirstPoint()) { return true; }
		else { return false; }
	}
	bool operator != (const Line& l2) const {
		if (GetFirstPoint() == l2.GetFirstPoint() && GetSecondPoint() == l2.GetSecondPoint()) { return false; }
		else if (GetFirstPoint() == l2.GetSecondPoint() && GetSecondPoint() == l2.GetFirstPoint()) { return false; }
		else { return true; }
	}

	int NextLineDeviation(const Line& l) { //return 2, if there is no common Point, 
										   //-1 if there is left deviation
										   //1 if there is right deviation
										   //0 if there is no deviation
		Point commonP, firstP, lastP, fp, lp;
		if (a == l.a) { commonP = a; firstP = b; lastP = l.b; }
		else if (a == l.b) { commonP = a; firstP = b; lastP = l.a; }
		else if (b == l.b) { commonP = b; firstP = a; lastP = l.a; }
		else if (b == l.a) { commonP = b; firstP = a; lastP = l.b; }
		else { return 2; }

		firstP.x -= commonP.x;
		firstP.y -= commonP.y;
		lastP.x -= commonP.x;
		lastP.y -= commonP.y;

		fp.x = firstP.x * cos(RAD * angle) - firstP.y * sin(RAD * angle);
		fp.y = firstP.x * sin(RAD * angle) + firstP.y * cos(RAD * angle);
		lp.x = lastP.x * cos(RAD * angle) - lastP.y * sin(RAD * angle);
		lp.y = lastP.x * sin(RAD * angle) + lastP.y * cos(RAD * angle);

		if (lp.y < 0) { return -1;  }
		else if (lp.y > 0) { return 1;  }
		else { return 0;  }
	}

	bool IsOnLine(const Point& p) {
		if (p.y <= p.x * k + kb + EPSILON && p.y >= p.x * k + kb - EPSILON) { return true; }
		else { return false; }
	}

	bool IsEqual(const Line& l) {
		if (length == l.GetLength() && angle == l.GetAngle()) { return true; }
		else if (length == l.GetLength() && angle == l.GetAngle() + 180) { return true; }
		else if (length == l.GetLength() && angle == l.GetAngle() - 180) { return true; }
		else { return false; }
	}

	void Print(sf::RenderWindow& window, sf::Color c) const {
		sf::VertexArray line;

		line.setPrimitiveType(sf::LinesStrip);
		line.append(sf::Vertex(sf::Vector2f(a.x, a.y), c));
		
		line.append(sf::Vertex(sf::Vector2f(b.x, b.y), c));
		window.draw(line);

	}

	Point mediumPoint() const {
		return Point((a.x + b.x) / 2, (a.y + b.y) / 2);
	}

	Point intersectionPoint(const Line& i) const {
		if (GetK() == i.GetK()) { return Point(0, 0); }
		else {
			double x = (i.GetKb() - GetKb()) / (GetK() - i.GetK());
			double y = x * GetK() + GetKb();
			return Point(x, y);
		}
	}
};

