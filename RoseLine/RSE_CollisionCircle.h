#pragma 

#include "RSE_CollisionBox.h"
#include "RSE_CollisionArea.h"
class RSE_CollisionCircle : public RSE_CollisionArea
{
public:

	virtual void update(RSE_GameObject*);
	virtual bool collidesWith(RSE_CollisionBox*);
	virtual bool collidesWith(RSE_CollisionCircle*);

	RSE_CollisionCircle();
	virtual ~RSE_CollisionCircle();
};

