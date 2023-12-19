// SimpleDDA.cpp : Defines the exported functions for the DLL.
//

#include "pch.h"
#include "framework.h"
#include "SimpleDDA.h"


// This is an example of an exported variable
SIMPLEDDA_API int nSimpleDDA=0;

// This is an example of an exported function.
SIMPLEDDA_API int fnSimpleDDA(void)
{
    return 0;
}

SimpleDDA::SimpleDDA()
{

}

SimpleDDA::~SimpleDDA()
{

}

void SimpleDDA::drawLineBySimpleDDA(Line& l, vector<float>& pixelVertices)
{
    float x1 = l.p1().x();
    float y1 = l.p1().y();
    float x2 = l.p2().x();
    float y2 = l.p2().y();

    float dx = abs(x2 - x1);
    float dy = abs(y2 - y1);
    float deltaX;
    float deltaY;
    if (dy > dx)
    {
        deltaX = dx / dy;
        deltaY = dy / dy;
    }
    else
    {
        deltaX = dx / dx;
        deltaY = dy / dx;
    }
    while (x1 < x2)
    {
        pixelVertices.push_back((round(x1), round(y1)));
        pixelVertices.push_back((round(x1) + 1, round(y1)));
        pixelVertices.push_back((round(x1) + 1, round(y1) + 1));
        pixelVertices.push_back((round(x1), round(y1) + 1));
        x1 = deltaX + x1;
        y1 = deltaY + y1;
    }


}