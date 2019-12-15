#pragma once
class RSE_Point
{
public:
	float x;
	float y;
	RSE_Point(float, float);
	float distanceTo(RSE_Point*);
	~RSE_Point();
};

