# Sutherland-Hodgman Polygon Clipping Algorithm
The Sutherland-Hodgman algorithm is a polygon clipping algorithm used in computer graphics to clip a polygon against a rectangular window. It determines the visible portions of a polygon within a defined clipping area.

## Overview
This project implements the Sutherland-Hodgman algorithm for polygon clipping. The algorithm processes vertices of a polygon against a clipping window to retain the visible segments of the polygon.

## Features
SutherlandHodgman Class
Provides methods to perform polygon clipping against a rectangular window.
Determines the visible segments of the input polygon within the defined clipping area.
## Usage
Include the SutherlandHodgman.h header file in your project.
Ensure the SutherlandHodgman library or source files are available.
Create an instance of the SutherlandHodgman class.
Clipping a Polygon
Use the clipPolygon method, providing the coordinates of the polygon vertices and the clipping window.
