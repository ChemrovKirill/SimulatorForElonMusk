#include "Polygon.h"

using namespace gs;

Polygon::Polygon(const std::vector<Point>& v)
	: vertices(v) {
	for (size_t i = 0; i < vertices.size(); ++i) {
		sides.push_back(Line(vertices[i], vertices[(i + 1) % vertices.size()]));
	}
}

Polygon::Polygon(const std::vector<Line>& l)
	: sides(l) {
	for (const auto& s : sides) {
		vertices.push_back(s.point(1));
	}
}

std::vector<Point> Polygon::getVertices() const {
	return vertices;
}
size_t Polygon::verticesCount() const {
	return vertices.size();
}
bool Polygon::isConvex() const {
	for (size_t i = 0; i < verticesCount(); ++i) {
		std::vector<Point> v;
		for (size_t j = 0; j < verticesCount(); ++j) {
			if (i != j) {
				v.push_back(vertices[j]);
			}
		}
		Polygon temp(v);
		if (temp.containsPoint(vertices[i]) == 1) {
			return false;
		}
	}
	return true;
}
bool Polygon::isPolygon() const {
	if (verticesCount() < 3) {
		return false;
	}
	for (size_t i = 0; i < sides.size(); i++) {
		if (sides[i].Angle() == sides[(i + 1) % sides.size()].Angle()) {
			return false;
		}
	}
	for (const auto& s1 : sides) {
		for (const auto& s2 : sides) {
			if (s1.IntersectsInside(s2)) {
				return false;
			}
		}
	}
	return true;
}

double Polygon::perimeter() const {
	double P = 0;
	for (const auto& s : sides) {
		P += s.Length();
	}
	return P;
}
double Polygon::area() const {
	double S = vertices[0].x * (vertices[1].y - vertices[vertices.size() - 1].y);
	for (size_t i = 1; i < vertices.size()-1; ++i) {
		S += vertices[i].x * (vertices[i + 1].y - vertices[i - 1].y);
	}
	S += vertices[vertices.size() - 1].x * (vertices[0].y - vertices[vertices.size() - 2].y);
	return abs(S / 2);
}
bool Polygon::operator==(const Shape& sh) const {
	const Polygon& another = dynamic_cast<const Polygon&>(sh);
	if (verticesCount() != another.verticesCount()) {
		return false;
	}
	for (size_t i = 0; i < verticesCount(); ++i) {
		if (vertices[i] != another.vertices[i]) {
			return false;
		}
	}
	return true;
}

bool Polygon::isCongruentTo(const Shape& sh) const {
	const Polygon& another = dynamic_cast<const Polygon&>(sh);
	if (verticesCount() != another.verticesCount()) {
		return false;
	}
	for (size_t start = 0; start < verticesCount(); ++start) {
		int i;
		double angle_1 = sides[0].Angle();
		double angle_2 = another.sides[start].Angle();
		for (i = 0; i < verticesCount(); ++i) {
			if (abs(sides[i].Length() - (another.sides[(start + i) % verticesCount()].Length())) > EPSILON) {
				break;
			}
			if (abs(abs(sides[i].Angle() - angle_1) - abs(another.sides[(start + i) % verticesCount()].Angle() - angle_2)) > EPSILON) {
				break;
			}
		}
		if (i == verticesCount()) {
			return true;
		}
		for (i = 0; i < verticesCount(); ++i) {
			if (abs(sides[i].Length() - (another.sides[(verticesCount() + start - i) % verticesCount()].Length())) > EPSILON) {
				break;
			}
			if (abs(abs(sides[i].Angle() - angle_1) - abs(another.sides[(verticesCount() + start - i) % verticesCount()].Angle() - angle_2)) > EPSILON) {
				break;
			}
		}
		if (i == verticesCount()) {
			return true;
		}
	}
	return false;
}

bool Polygon::containsPoint(const Point& point) const {
	double TrArea=0;
	for (const auto& s : sides) {
		Polygon triangle({ point, s.point(1), s.point(2) });
		TrArea += triangle.area();
	}
	return TrArea == area();
}