#include "Triangle.h"

using namespace gs;

Triangle::Triangle(const Point& p1, const Point& p2, const Point& p3)
	:Polygon({ p1,p2,p3 }) {}

Circle Triangle::circumscribedCircle() {
	Line a = sides[0];
	Point mid_a = a.mid();
	Line a_norm(mid_a, a.Angle() + 90, 1);
	Line b = sides[1];
	Point mid_b = b.mid();
	Line b_norm(mid_b, b.Angle() + 90, 1);
	Point center = a_norm.IntersectionPoint(b_norm);
	Line radius(center, vertices[0]);
	return Circle(center, radius.Length());
}

Circle Triangle::inscribedCircle() {
	Line bis_01(sides[0].point(2), (sides[0].Angle() + sides[1].Angle()) / 2.0, 1);
	if (sides[2].Intersects(bis_01) == 0) {
		bis_01 = Line(sides[0].point(2), (sides[0].Angle() + sides[1].Angle()) / 2.0 + 90, 1);
	}
	Line bis_12(sides[1].point(2), (sides[1].Angle() + sides[2].Angle()) / 2.0, 1);
	if (sides[0].Intersects(bis_12) == 0) {
		bis_12 = Line(sides[1].point(2), (sides[1].Angle() + sides[2].Angle()) / 2.0 + 90, 1);
	}
	Point center = bis_01.IntersectionPoint(bis_12);
	return Circle(center, 2*area()/perimeter());
}

Point Triangle::centroid() {
	Point mid_1 = sides[1].mid();
	Point mid_2 = sides[2].mid();
	Line med_1(mid_1, vertices[0]);
	Line med_2(mid_2, vertices[1]);
	return med_2.IntersectionPoint(med_1);
}

Point Triangle::orthocenter() {
	Line h0(vertices[0], sides[1].Angle() + 90, 1);
	Line h1(vertices[1], sides[2].Angle() + 90, 1);
	return h0.IntersectionPoint(h1);
}

Line Triangle::EulerLine() {
	return Line(orthocenter(), circumscribedCircle().center());
}

Circle Triangle::ninePointsCircle() {
	Triangle t_mids(sides[0].mid(), sides[1].mid(), sides[2].mid());
	return t_mids.circumscribedCircle();
}