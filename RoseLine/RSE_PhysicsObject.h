#pragma once

#include "RSE_Vector.h"
#include "RSE_GameObject.h"
#include "RSE_CollisionBox.h"
#include "RSE_CollisionArea.h"

class RSE_PhysicsObject : public RSE_GameObject
{
	RSE_CollisionBox* collision;
	const float GRAVITY = 0.0002f;
private: 
	int getCollisionValue(int, int, int, int, int);
	int getPriorityFromCollisionValue(int);
	int getActionFromValueAndPriority(int, int);
	int getDirectionsToLimit(int, int, int, int);

public:

	bool rigid = true;

	RSE_Vector* movementVector;
	bool falling = false;
	bool gravity = true;

	virtual int update(); // update now has colission methods included
	bool collidesWith(RSE_PhysicsObject*);
	void bump(float, float);
	void reset();
	void setCollision();

	RSE_PhysicsObject(float, float);
	RSE_PhysicsObject(float, float, string);
	virtual ~RSE_PhysicsObject();
};