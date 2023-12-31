#include "stdafx.h"
#include "Grid.h"

Grid::Grid()
{
    return;
}



Grid::Grid(QVector<GLfloat>& vertices, QVector<GLfloat>& colors, int gridSize)
{
    drawGrid(vertices, colors, gridSize);
}

Grid::~Grid()
{
}

void Grid::drawGrid(QVector<GLfloat>& vertices, QVector<GLfloat>& colors, int gridSize) {
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