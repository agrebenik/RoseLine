#pragma once

#include "RSE_GameObject.h"
#include "RSE_CollisionArea.h"
class RSE_CollisionBox : public RSE_CollisionArea
{
public:
	float px = 0;
	float py = 0;
	float ow = 0;
	float oh = 0;

	virtual void update(RSE_GameObject*);
	virtual bool collidesWith(RSE_CollisionBox*);

	RSE_CollisionBox();
	virtual ~RSE_CollisionBox();
};

