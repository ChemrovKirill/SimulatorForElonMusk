#pragma once
#include <iostream>
#include <utility>

namespace gs {

#define PI 3.141593
#define RAD_TO_DEG (180.0/PI)
#define DEG_TO_RAD (PI/180.0)
#define EPSILON 0.0001

	struct Point {
		double x;
		double y;
		Point() : x(0), y(0) {}
		Point(const double& _x, const double& _y)
			:x(_x), y(_y) {}

		bool operator == (const Point&) const;
		bool operator != (const Point&) const;
	};

}

std::ostream& operator << (std::ostream&, const gs::Point&);