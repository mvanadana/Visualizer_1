#pragma once
#include "pch.h"

class GEOMETRY_API Point
{
public:
    Point(double inX, double inY);
    Point(double inX, double inY, double inZ);
    Point();
    ~Point();

    double x() const;
    double y() const;
    double z() const;
    void setX(double x);
    void setY(double y);
    void setZ(double z);

private:
    double mX;
    double mY;
    double mZ;
};
