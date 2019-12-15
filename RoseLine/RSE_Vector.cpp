#include "RSE_Vector.h"
#include "ENM_Direction.h"

void RSE_Vector::operator+=(const RSE_Vector* other) {
	dx += other->dx;
	dy += other->dy;
}

void RSE_Vector::operator-=(const RSE_Vector* other) {
	dx -= other->dx;
	dy -= other->dy;
}

void RSE_Vector::operator*=(const RSE_Vector* other) {
	dx *= other->dx;
	dy *= other->dy;
}

void RSE_Vector::operator/=(const RSE_Vector* other) {
	dx /= other->dx;
	dy /= other->dy;
}

void RSE_Vector::zero() {
	dx = 0;
	dy = 0;
}

int RSE_Vector::getDirection() {
	return (dx > 0 ? Right : dx < 0 ? Left : NoDirection) + (dy > 0 ? Down : dy < 0 ? Up : NoDirection);
}

RSE_Vector::RSE_Vector(float vDx, float vDy) {
	dx = vDx;
	dy = vDy;
}

RSE_Vector::~RSE_Vector() {
}
