#pragma once

#include "RSE_Point.h"

class RSE_Line
{
public:
	RSE_Point * p1;
	RSE_Point* p2;
	float slope;
	RSE_Line(RSE_Point*, RSE_Point*);
	float getYatX(float);
	float getXatY(float);
	bool intersects(RSE_Line*);
	RSE_Point* intersectionPoint(RSE_Line*);
	~RSE_Line();
};

