// SutherlandHodgeman.cpp : Defines the exported functions for the DLL.
//

#include "pch.h"
#include "framework.h"
#include "SutherlandHodgeman.h"

// This is an example of an exported variable
SUTHERLANDHODGEMAN_API int nSutherlandHodgeman = 0;

// This is an example of an exported function.
SUTHERLANDHODGEMAN_API int fnSutherlandHodgeman(void)
{
    return 0;
}

// This is the constructor of a class that has been exported.
SutherlandHodgeman::SutherlandHodgeman()
{
}

SutherlandHodgeman::SutherlandHodgeman(const Shape& region, const Shape& polygon)
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

        Line& line = mPolygon.getShape().at(i);
        double linePoint1X = l.p1().x();
        double linePoint1Y = l.p1().y();
        double linePoint2X = l.p2().x();
        double linePoint2Y = l.p2().y();
        double ReferencelinePoint1X = line.p1().x();
        double ReferencelinePoint1Y = line.p1().y();
        double ReferencelinePoint2X = line.p2().x();
        double ReferencelinePoint2Y = line.p2().y();

        double i_pos = (linePoint2X - linePoint1X) * (ReferencelinePoint1Y - linePoint1Y) - (linePoint2Y - linePoint1Y) * (ReferencelinePoint1X - linePoint1X);

        double k_pos = (linePoint2X - linePoint1X) * (ReferencelinePoint2Y - linePoint1Y) - (linePoint2Y - linePoint1Y) * (ReferencelinePoint2X - linePoint1X);

        if (i_pos < 0 && k_pos < 0)
        {
            newPoints.push_back(line.p2());
            newPolySize++;
        }
        else if (i_pos >= 0 && k_pos < 0)
        {
            double x = xIntersect(l, line);
            double y = yIntersect(l, line);
            Point p(x, y);
            newPoints.push_back(p);
            newPolySize++;
            newPoints.push_back(line.p2());
            newPolySize++;
        }
        else if (i_pos < 0 && k_pos >= 0)
        {
            double x = xIntersect(l, line);
            double y = yIntersect(l, line);
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
    double line1Point1X = l1.p1().x();
    double line1Point1Y = l1.p1().y();
    double line1Point2X = l1.p2().x();
    double line1Point2Y = l1.p2().y();
    double line2Point1X = l2.p1().x();
    double line2Point1Y = l2.p1().y();
    double line2Point2X = l2.p2().x();
    double line2Point2Y = l2.p2().y();

    double num = (line1Point1X * line1Point2Y - line1Point1Y * line1Point2X) * (line2Point1X - line2Point2X) - (line1Point1X - line1Point2X) * (line2Point1X * line2Point2Y - line2Point1Y * line2Point2X);
    double den = (line1Point1X - line1Point2X) * (line2Point1Y - line2Point2Y) - (line1Point1Y - line1Point2Y) * (line2Point1X - line2Point2X);
    return num / den;
}
double SutherlandHodgeman::yIntersect(Line l1, Line l2)
{
    double line1Point1X = l1.p1().x();
    double line1Point1Y = l1.p1().y();
    double line1Point2X = l1.p2().x();
    double line1Point2Y = l1.p2().y();
    double line2Point1X = l2.p1().x();
    double line2Point1Y = l2.p1().y();
    double line2Point2X = l2.p2().x();
    double line2Point2Y = l2.p2().y();

    double num = (line1Point1X * line1Point2Y - line1Point1Y * line1Point2X) * (line2Point1Y - line2Point2Y) - (line1Point1Y - line1Point2Y) * (line2Point1X * line2Point2Y - line2Point1Y * line2Point2X);
    double den = (line1Point1X - line1Point2X) * (line2Point1Y - line2Point2Y) - (line1Point1Y - line1Point2Y) * (line2Point1X - line2Point2X);
    return num / den;
}
