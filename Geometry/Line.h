#pragma once
#include "Point.h"

class GEOMETRY_API Line
{
public:
    Line(const Point& p1, const Point& p2); // Use copies instead of references
    Line(const Line& other);
    Line();
    ~Line();
    Line& operator=(const Line&);

    const Point& p1() const; // Return Point reference
    const Point& p2() const;

private:
    Point mP1; // Use copies instead of references
    Point mP2;
};
