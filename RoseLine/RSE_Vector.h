#pragma once
class RSE_Vector
{
public:

	float dx, dy;

	void operator+=(const RSE_Vector*);
	void operator-=(const RSE_Vector*);
	void operator*=(const RSE_Vector*);
	void operator/=(const RSE_Vector*);

	void zero();
	int getDirection();

	RSE_Vector(float, float);
	~RSE_Vector();
};

