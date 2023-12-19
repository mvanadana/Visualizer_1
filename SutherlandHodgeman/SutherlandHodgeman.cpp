// SutherlandHodgeman.cpp : Defines the exported functions for the DLL.
//

#include "pch.h"
#include "framework.h"
#include "SutherlandHodgeman.h"


// This is an example of an exported variable
SUTHERLANDHODGEMAN_API int nSutherlandHodgeman=0;

// This is an example of an exported function.
SUTHERLANDHODGEMAN_API int fnSutherlandHodgeman(void)
{
    return 0;
}

// This is the constructor of a class that has been exported.
SutherlandHodgeman::SutherlandHodgeman()
{
 
}


SutherlandHodgeman::SutherlandHodgeman(Shape region, Shape polygon)
    : mRegion(region),
    mPolygon(polygon)
{
}

SutherlandHodgeman::~SutherlandHodgeman()
{
}

Shape SutherlandHodgeman::getClippedPolygon()
{
    int size = mRegion.getSize();
    for (int i = 0; i < size; i++)
    {
        std::vector<Line> shape = mRegion.getShape();
        clipAlongLine(shape.at(i));
    }
    return Shape(mPolygon);
}


void SutherlandHodgeman::clipAlongLine(Line l)
{
    std::vector<Point> newPoints;
    int newPolySize = 0;

    for (int i = 0; i < mPolygon.getSize(); i++)
    {

        Line& li = mPolygon.getShape().at(i);
        double i_pos = (l.p2().x() - l.p1().x()) * (li.p1().y() - l.p1().y()) - (l.p2().y() - l.p1().y()) * (li.p1().x() - l.p1().x());

        double k_pos = (l.p2().x() - l.p1().x()) * (li.p2().y() - l.p1().y()) - (l.p2().y() - l.p1().y()) * (li.p2().x() - l.p1().x());

        if (i_pos < 0 && k_pos < 0)
        {
            newPoints.push_back(li.p2());
            newPolySize++;
        }
        else if (i_pos >= 0 && k_pos < 0)
        {
            double x = xIntersect(l, li);
            double y = yIntersect(l, li);
            Point p(x, y);
            newPoints.push_back(p);
            newPolySize++;
            newPoints.push_back(li.p2());
            newPolySize++;
        }
        else if (i_pos < 0 && k_pos >= 0)
        {
            double x = xIntersect(l, li);
            double y = yIntersect(l, li);
            Point p(x, y);
            newPoints.push_back(p);
            newPolySize++;
        }
    }

    std::vector<Line> polyLine;

    for (int i = 0; i < newPolySize; i++)
    {
        polyLine.push_back(Line(newPoints.at(i), newPoints.at((i + 1) % newPoints.size())));
    }

    mPolygon.setShape(polyLine);
}

double SutherlandHodgeman::xIntersect(Line l1, Line l2)
{
    double num = (l1.p1().x() * l1.p2().y() - l1.p1().y() * l1.p2().x()) * (l2.p1().x() - l2.p2().x()) - (l1.p1().x() - l1.p2().x()) * (l2.p1().x() * l2.p2().y() - l2.p1().y() * l2.p2().x());
    double den = (l1.p1().x() - l1.p2().x()) * (l2.p1().y() - l2.p2().y()) - (l1.p1().y() - l1.p2().y()) * (l2.p1().x() - l2.p2().x());
    return num / den;
}
double SutherlandHodgeman::yIntersect(Line l1, Line l2)
{
    double num = (l1.p1().x() * l1.p2().y() - l1.p1().y() * l1.p2().x()) * (l2.p1().y() - l2.p2().y()) - (l1.p1().y() - l1.p2().y()) * (l2.p1().x() * l2.p2().y() - l2.p1().y() * l2.p2().x());
    double den = (l1.p1().x() - l1.p2().x()) * (l2.p1().y() - l2.p2().y()) - (l1.p1().y() - l1.p2().y()) * (l2.p1().x() - l2.p2().x());
    return num / den;
}