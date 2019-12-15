#include "RSE_Point.h"
#include <math.h>

RSE_Point::RSE_Point(float xPox, float yPox) {
	x = xPox;
	y = yPox;
}

float RSE_Point::distanceTo(RSE_Point* ptr_other) {
	float dx = ptr_other->x - this->x;
	float dy = ptr_other->y - this->y;
	return (float)sqrt(pow(dx, 2) + pow(dy, 2));
}

RSE_Point::~RSE_Point() { }
