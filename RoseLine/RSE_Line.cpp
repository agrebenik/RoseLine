#include "RSE_Line.h"

#include "RSE_Point.h"

RSE_Line::RSE_Line(RSE_Point* ptr_a, RSE_Point* ptr_b) {
	p1 = ptr_a;
	p2 = ptr_b;
	slope = (ptr_a->y - ptr_b->y) / (ptr_a->x - ptr_b->x);
}

float RSE_Line::getYatX(float x) {
	return -slope * (p1->x - x) - p1->y;
}

float RSE_Line::getXatY(float y) {
	return -(p1->y - y) / slope - p1->x;
}

bool RSE_Line::intersects(RSE_Line* ptr_other) {
	double a1 = p2->y - p1->y;
	double b1 = p1->x - p2->x;
	double c1 = a1 * (p1->x) + b1 * (p1->y);

	double a2 = ptr_other->p2->y - ptr_other->p1->y;
	double b2 = ptr_other->p1->x - ptr_other->p2->x;
	double c2 = a2 * (ptr_other->p1->x) + b2 * (ptr_other->p1->y);

	double dt = a1 * b2 - a2 * b1;

	return dt != 0;
}

RSE_Point* RSE_Line::intersectionPoint(RSE_Line* ptr_other) {
	double a1 = p2->y - p1->y;
	double b1 = p1->x - p2->x;
	double c1 = a1 * (p1->x) + b1 * (p1->y);

	double a2 = ptr_other->p2->y - ptr_other->p1->y;
	double b2 = ptr_other->p1->x - ptr_other->p2->x;
	double c2 = a2 * (ptr_other->p1->x) + b2 * (ptr_other->p1->y);

	double dt = a1 * b2 - a2 * b1;

	if (dt != 0)
	{
		double x = (b2*c1 - b1 * c2) / dt;
		double y = (a1*c2 - a2 * c1) / dt;
		return new RSE_Point(x, y);
	}
	return nullptr;
}

RSE_Line::~RSE_Line() { }
