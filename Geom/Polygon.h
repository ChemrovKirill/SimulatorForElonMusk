#pragma once

#include<vector>

#include"Line.h"
#include"shape.h"

class polygon : public shape {
protected:
	std::vector<Point> vertices;
	std::vector<Line> lines;
public:
	polygon(std::vector<Point> vp) : vertices(vp) {
		for (int i = 0; i < vertices.size() - 1; ++i) {
			lines.push_back(Line(vertices[i], vertices[i + 1]));
		}
		lines.push_back(Line(vertices[vertices.size() - 1], vertices[0]));
	}
	polygon(std::vector<Line> vl) : lines(vl) {
		vertices.push_back(lines[0].GetFirstPoint());
		for (int i = 1; i < lines.size(); ++i) {
			if (lines[i].GetFirstPoint() != vertices[i - 1]) {
				vertices.push_back(lines[i].GetFirstPoint());
			}
			else {
				vertices.push_back(lines[i].GetSecondPoint());
			}
		}
	}
	polygon(const polygon& p) : vertices(p.GetVertices()), lines(p.GetLines()) {};

	std::vector<Point> GetVertices() const { return vertices; }
	std::vector<Line> GetLines() const { return lines; }

	double perimeter() const {
		float per = 0;
		for (int i = 0; i < lines.size(); ++i) {
			per += lines[i].GetLength();
		}
		return per;
	};
	double area() const {
		double area = 0;
		area += vertices[vertices.size() - 1].x * vertices[0].y;
		for (int i = 0; vertices.size() - 1; ++i) {
			area += vertices[i].x * vertices[i + 1].y;
		}
		area -= vertices[vertices.size() - 1].y * vertices[0].x;
		for (int i = 0; vertices.size() - 1; ++i) {
			area -= vertices[i].y * vertices[i + 1].x;
		}
		return abs(area / 2);
	}
	bool operator==(const shape& shape) const { 
		const polygon& another = dynamic_cast<const polygon&>(shape);
		if (VerticesCount() != another.VerticesCount()) { return false; }
		else {
			for (int i = 0; i < vertices.size(); ++i) {
				if (vertices[i] != another.GetVertices()[i]) { return false; }
			}	
			return true;
		}
	};
	bool isCongruentTo(const shape& shape) const { 
		const polygon& another = dynamic_cast<const polygon&>(shape);
		if (VerticesCount() != another.VerticesCount()) { return false; }

		std::vector<Line> v2 = lines;
		
		for (int i = v2.size() - 1; i >= 0; --i) {
			for (Line ii : another.GetLines()) {
				if (ii.IsEqual(v2[i])) { v2.pop_back(); }
			}
		}
		if (v2.empty() == false) { return false; }
	
		return true;
	};

	bool containsPoint(const Point& p) const { 
		double an = -90;
		bool success_cast = false;
		int intersection = 0;

		while (success_cast == false) {
			an += 10;
			Line ray(p, an, 1);
			for (Point i : vertices) {
				if (p == i) { return true; }
				if (i.y == i.x * ray.GetK() + ray.GetKb()) { break; }
			}
			success_cast = true;
		}
		Line ray(p, an, 1000);
		for (Line i : lines) {
			Point int_p(ray.intersectionPoint(i));
			if (((int_p.x >= i.GetFirstPoint().x&& int_p.x >= i.GetSecondPoint().x) ||
					 (int_p.x <= i.GetFirstPoint().x && int_p.x <= i.GetSecondPoint().x)) &&
					 ((int_p.y >= i.GetFirstPoint().y&& int_p.y >= i.GetSecondPoint().y) ||
					 (int_p.y <= i.GetFirstPoint().y && int_p.y <= i.GetSecondPoint().y))) {}
			else if (ray.GetFirstPoint().x > int_p.x) {}
			else { ++intersection; }
			}
		if (intersection % 2 == 1) { return	true; }
		else { return false; }
	};

	int VerticesCount() const { return vertices.size(); }
	bool IsConvex() {
		int dev = lines[lines.size() - 1].NextLineDeviation(lines[0]);
		for (int i = 0; i < lines.size() - 1; ++i) {
			if (lines[i].NextLineDeviation(lines[i + 1]) != dev) { return true; }
		}
		return false;
	}
	bool IsPolygon(const std::vector<Point>& v) {
		if (v[v.size()] == v[0]) { return false; }
		for (int i = 0; i < v.size() - 1; ++i) {
			if (v[i] == v[i + 1]) { return false; }
		}

		Line l1(v[v.size() - 2], v[0]);
		if (l1.IsOnLine(v[v.size() - 1]) == true) { return false; }
		Line l2(v[v.size() - 1], v[1]);
		if (l2.IsOnLine(v[0]) == true) { return false; }
		for (int i = 0; i < v.size() - 2; ++i) {
			Line l(v[i], v[i + 2]);
			if (l.IsOnLine(v[i + 1]) == true) { return false; }
		}

		return true;
	}

	void Print(RenderWindow& window) const {
		for (Line i : GetLines()) { i.Print(window); }
	}
};

