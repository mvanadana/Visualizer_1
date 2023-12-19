#include "pch.h"
#include "framework.h"
#include "Grid.h"


// This is an example of an exported variable
GRID_API int nGrid=0;

// This is an example of an exported function.
GRID_API int fnGrid(void)
{
    return 0;
}

// This is the constructor of a class that has been exported.
Grid::Grid()
{
    return;
}



Grid::Grid(std::vector<float>& vertices, std::vector<float>& colors, int gridSize)
{
    drawGrid(vertices, colors, gridSize);
}

Grid::~Grid()
{
}

void Grid::drawGrid(std::vector<float>& vertices, std::vector<float>& colors, int gridSize) {
    //const float gridSize = 8.0f;  // Adjust the grid size as needed
    const float step = 1.0f;

    // Draw horizontal grid lines
    for (float y = -gridSize / 2.0f; y <= gridSize / 2.0f; y += step)
    {
        vertices.push_back(-gridSize / 2.0f);
        vertices.push_back(y);
        vertices.push_back(gridSize / 2.0f);
        vertices.push_back(y);

        colors.push_back(1.0f);
        colors.push_back(1.0f);
        colors.push_back(1.0f);
        colors.push_back(1.0f);
        colors.push_back(1.0f);
        colors.push_back(1.0f);
    }

    // Draw vertical grid lines
    for (float x = -gridSize / 2.0f; x <= gridSize / 2.0f; x += step)
    {
        vertices.push_back(x);
        vertices.push_back(-gridSize / 2.0f);
        vertices.push_back(x);
        vertices.push_back(gridSize / 2.0f);

        colors.push_back(1.0f);
        colors.push_back(1.0f);
        colors.push_back(1.0f);
        colors.push_back(1.0f);
        colors.push_back(1.0f);
        colors.push_back(1.0f);
    }
}