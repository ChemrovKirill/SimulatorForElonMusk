#pragma once

#include"Point.h"

class shape {
public:
    virtual double perimeter() const = 0;
    virtual double area() const = 0;
    virtual bool operator==(const shape& another) const = 0;
    virtual bool isCongruentTo(const shape& another) const = 0;
    virtual bool containsPoint(const Point& p) const = 0;
    virtual ~shape() {}
};