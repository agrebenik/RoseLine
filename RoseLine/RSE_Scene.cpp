#include "RSE_Scene.h"
#include "RSE_GameObject.h"
#include "RSE_MAN_GameObject.h"

RSE_Scene::RSE_Scene(float x, float y) : RSE_GameObject(x, y) { }

void RSE_Scene::Init() { 
}

RSE_GameObject* RSE_Scene::addGameObject(RSE_GameObject* ptr_obj) {
	objectsArray.push_front(ptr_obj);
	return ptr_obj;
}

int RSE_Scene::draw() {
	list<RSE_GameObject*>::iterator it;
	for (it = objectsArray.begin(); it != objectsArray.end(); it++) {
		RSE_GameObject* ptr_cur = *it;
		if ((ptr_cur->destoryOffScreen && !RSE_MAN_GameObject::isVisibleOnScreen(ptr_cur)) || ptr_cur->garbage) { }
		else {
			ptr_cur->shift(position->x, position->y);
			ptr_cur->draw();
			ptr_cur->shift(-position->x, -position->y);
		}
	}
	return 0;
}

int RSE_Scene::update() {
	list<RSE_GameObject*>::iterator it;
	for (it = objectsArray.begin(); it != objectsArray.end(); it++) {
		RSE_GameObject* ptr_cur = *it;
		if ((ptr_cur->destoryOffScreen && !RSE_MAN_GameObject::isVisibleOnScreen(ptr_cur)) || ptr_cur->garbage) {
			garbageArray.push(ptr_cur);
		}
		else {
			ptr_cur->shift(position->x, position->y);
			ptr_cur->update();
			ptr_cur->shift(-position->x, -position->y);
		}
	}
	while (!garbageArray.empty()) {
		RSE_GameObject* ptr_rem = garbageArray.top();
		garbageArray.pop();
		objectsArray.remove(ptr_rem);
		delete ptr_rem;
	}
	return 0;
}

RSE_Scene::~RSE_Scene() { }
