// The following ifdef block is the standard way of creating macros which make exporting
// from a DLL simpler. All files within this DLL are compiled with the GRID_EXPORTS
// symbol defined on the command line. This symbol should not be defined on any project
// that uses this DLL. This way any other project whose source files include this file see
// GRID_API functions as being imported from a DLL, whereas this DLL sees symbols
// defined with this macro as being exported.

// This class is exported from the dll
#pragma once
#include <vector>
#include "pch.h"

class GRID_API Grid {
public:
	Grid(void);
    Grid(std::vector<float>& vertices, std::vector<float>& colors, int gridSize);
    ~Grid();
 private:
    void drawGrid(std::vector<float>& vertices, std::vector<float>& colors, int gridSize);
    
};

extern GRID_API int nGrid;

GRID_API int fnGrid(void);
