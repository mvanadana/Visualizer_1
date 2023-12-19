// The following ifdef block is the standard way of creating macros which make exporting
// from a DLL simpler. All files within this DLL are compiled with the SIMPLEDDA_EXPORTS
// symbol defined on the command line. This symbol should not be defined on any project
// that uses this DLL. This way any other project whose source files include this file see
// SIMPLEDDA_API functions as being imported from a DLL, whereas this DLL sees symbols
// defined with this macro as being exported.

// This class is exported from the dll
#pragma once
#include "Line.h"
#include <vector>
#include "pch.h"

using namespace std;
class SIMPLEDDA_API SimpleDDA {

public:
	SimpleDDA();
	~SimpleDDA();

public:
	//void drawGrid(vector<float>& vertices, vector<float>& colors);
	void drawLineBySimpleDDA(Line& line, vector<float>& mVertices);

public:
	vector<float> mVertices;
	vector<float> mColors;
};

extern SIMPLEDDA_API int nSimpleDDA;

SIMPLEDDA_API int fnSimpleDDA(void);



#pragma once
#include "Line.h"


