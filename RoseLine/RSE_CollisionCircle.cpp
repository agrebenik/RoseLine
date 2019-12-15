#include "RSE_CollisionCircle.h"

void RSE_CollisionCircle::update(RSE_GameObject* obj) { }

bool RSE_CollisionCircle::collidesWith(RSE_CollisionCircle* c) {
	return false;
}

bool RSE_CollisionCircle::collidesWith(RSE_CollisionBox* b) {
	return false;
}

RSE_CollisionCircle::RSE_CollisionCircle() { }
RSE_CollisionCircle::~RSE_CollisionCircle() { }
