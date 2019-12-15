#pragma once

#include <list>
#include <stack> 

#include "RSE_GameObject.h"

using namespace std;

class RSE_Scene : public RSE_GameObject
{
	stack<RSE_GameObject*> garbageArray;
	list<RSE_GameObject*> objectsArray;
public:
	RSE_Scene(float, float);
	virtual void Init();
	virtual int draw();
	virtual int update();
	RSE_GameObject* addGameObject(RSE_GameObject*);
	virtual ~RSE_Scene();
};

