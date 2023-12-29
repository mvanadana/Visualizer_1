#include "pch.h"
#include "Line.h"

Line::Line(const Point& p1, const Point& p2)
    : mP1(p1),
    mP2(p2)
{
}
Line::Line(const Line& other)
    : mP1(other.mP1),
    mP2(other.mP2)
{
    // You may need to copy other necessary data members if any
}
Line::Line()
{
}
Line::~Line()
{
}

const Point& Line::p1() const
{
    return mP1;
}

const Point& Line::p2() const
{
    return mP2;
}

Line& Line::operator=(const Line& other)
{
    if (this != &other) // Check for self-assignment
    {
        // Copy data members from 'other' to 'this'
        mP1 = other.mP1;
        mP2 = other.mP2;
    }
    return *this;
}
