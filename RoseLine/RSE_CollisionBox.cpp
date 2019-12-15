#include "RSE_CollisionBox.h"

#include <iostream>

using namespace std;

void RSE_CollisionBox::update(RSE_GameObject* obj) {
	px = obj->position->x - ow/2;
	py = obj->position->y - oh/2;
	ow = obj->w;
	oh = obj->h;
}

bool RSE_CollisionBox::collidesWith(RSE_CollisionBox* b) {
	float ax1 = px;
	float ax2 = px + ow;
	float ay1 = py + oh;
	float ay2 = py;
	float bx1 = b->px;
	float bx2 = b->px + b->ow;
	float by1 = b->py + b->oh;
	float by2 = b->py;
	//cout << "stt\n\tax1 = " << ax1 << "\n\tax2 = " << ax2 << "\n\tay1 = " << ay1 << "\n\tay2 = " << ay2;
	//cout << "\n\n\ybx1 = " << bx1 << "\n\tbx2 = " << bx2 << "\n\tby1 = " << by1 << "\n\tby2 = " << by2 << "\n";
	//cout << "colcheck\n\t[ ax1 < bx2: " << (ax1 < bx2) << " ]\n\t[ ax2 > bx1 " << (ax2 > bx1) << " ]\n\t[ ay1 > by2 " << (ay1 > by2) << " ]\n\t[ ay2 < by1 " << (ay2 < by1) << " ]\n\n";
	if (ax1 < bx2 && ax2 > bx1 && ay1 > by2 && ay2 < by1) {
		return true;
	}
	return false;
}

RSE_CollisionBox::RSE_CollisionBox() { }
RSE_CollisionBox::~RSE_CollisionBox() { }
