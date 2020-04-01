#pragma once

#include"Polygon.h"
#include"Circle.h"

class triangle : public polygon {
public:
    triangle(Point a, Point b, Point c) : polygon({a, b, c}) {}
    triangle(std::vector<Point> v) : polygon(v) {}
    triangle(const triangle& t) : polygon(t.GetVertices()) {}

    circle circumscribedCircle() const {
        Point m1(lines[0].mediumPoint()), m2(lines[1].mediumPoint()), int_p;
        Line h1(m1, lines[0].GetAngle() + 90, 100);
        Line h2(m2, lines[1].GetAngle() + 90, 100);
        int_p = h1.intersectionPoint(h2);
        Line l(int_p, vertices[0]);
        return circle(int_p, l.GetLength());
    }
    
    circle inscribedCircle() const {
        Point int0(lines[0].intersectionPoint(lines[1]));
        Point int1(lines[1].intersectionPoint(lines[2]));
        Point f0, f1, l0, l1, inter, inth;
        double angle0, angle1;

        if (lines[0].GetFirstPoint() == int0) { f0 = lines[0].GetSecondPoint(); }
        else { f0 = lines[0].GetFirstPoint(); }
        if (lines[1].GetFirstPoint() == int1) { f1 = lines[1].GetSecondPoint(); }
        else { f1 = lines[1].GetFirstPoint(); }

        if (lines[1].GetFirstPoint() == int0) { l0 = lines[1].GetSecondPoint(); }
        else { l0 = lines[1].GetFirstPoint(); }
        if (lines[2].GetFirstPoint() == int1) { l1 = lines[2].GetSecondPoint(); }
        else { l1 = lines[2].GetFirstPoint(); }
        
        if ((f0.x > int0.x&& l0.x > int0.x) || (f0.x < int0.x && l0.x < int0.x)) {
            angle0 = (lines[0].GetAngle() + lines[1].GetAngle()) / 2;
        }
        else {
            angle0 = 90 + ((lines[0].GetAngle() + lines[1].GetAngle())) / 2;
        }
        if ((f1.x > int1.x && l1.x > int1.x) || (f1.x < int1.x && l1.x < int1.x)) {
            angle1 = (lines[1].GetAngle() + lines[2].GetAngle()) / 2;
        }
        else {
            angle1 =  90 + ((lines[1].GetAngle() + lines[2].GetAngle())) / 2;
        }

        Line b1(int0, angle0, 100);
        Line b2(int1, angle1, 100);

        inter = b1.intersectionPoint(b2);

        Line h(inter, lines[0].GetAngle() - 90, 100);

        inth = h.intersectionPoint(lines[0]);

        Line h2(inter, inth);

        return circle(inter, h2.GetLength());
    }
    
    Point centroid() const {
        Point mid_a, mid_b, inter;

        Line l1(vertices[0], vertices[1]);
        Line l2(vertices[1], vertices[2]);

        mid_a = l1.mediumPoint();
        mid_b = l2.mediumPoint();

        Line l3(vertices[2], mid_a);
        Line l4(vertices[0], mid_b);
        return l4.intersectionPoint(l3);
    }
    Point orthocenter() const {




        Point m1(lines[0].mediumPoint()), m2(lines[1].mediumPoint()), int_p;
        Line line1(vertices[1], vertices[2]), line2(vertices[2], vertices[0]);
        Line h1(vertices[0], line1.GetAngle() + 90, 100);
        Line h2(vertices[1], line2.GetAngle() + 90, 100);
        int_p = h1.intersectionPoint(h2);
        return int_p;
    }
    
    Line EulerLine() const {
        return Line(orthocenter(), circumscribedCircle().center());
    }
    
    circle ninePointsCircle() const {
        triangle tr(lines[0].mediumPoint(), lines[1].mediumPoint(), lines[2].mediumPoint());
        return tr.circumscribedCircle();
    }
};