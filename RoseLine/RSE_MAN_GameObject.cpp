#include "RSE_MAN_GameObject.h"

#include <array>
#include <math.h>
#include <iostream>
#include "RSE_Time.h"
#include "RSE_MAN_Resource.h"

using namespace std;

stack<RSE_GameObject*> RSE_MAN_GameObject::garbageArray;
stack<int> RSE_MAN_GameObject::garbageInexes;

SDL_Window* RSE_MAN_GameObject::cmapDebugWindow;
SDL_Surface* RSE_MAN_GameObject::cmapDebugSurface;

float RSE_MAN_GameObject::SQUARE_SIZE = 5;
int RSE_MAN_GameObject::SCREEN_HEIGHT;
int RSE_MAN_GameObject::SCREEN_WIDTH;

int** RSE_MAN_GameObject::collisionArray;

int RSE_MAN_GameObject::pObjPtr = 0;
int RSE_MAN_GameObject::pObjSize = 0;
int RSE_MAN_GameObject::pObjLen = 1;

int RSE_MAN_GameObject::updateNumber = 0;

RSE_GameObject** RSE_MAN_GameObject::pObjectsArray;
list<RSE_GameObject*> RSE_MAN_GameObject::objectsArray;
RSE_EventHandler* RSE_MAN_GameObject::eventHandler;

void RSE_MAN_GameObject::Init(const int SW, const int SH) {
	RSE_MAN_GameObject::SCREEN_WIDTH = SW;
	RSE_MAN_GameObject::SCREEN_HEIGHT = SH;
	eventHandler = new RSE_EventHandler();
	float collisionArrayRows = ceil(SH / RSE_MAN_GameObject::SQUARE_SIZE);
	float collisionArrayColumns = ceil(SW / RSE_MAN_GameObject::SQUARE_SIZE);
	RSE_MAN_GameObject::collisionArray = new int*[collisionArrayRows];
	for (int i = 0; i < collisionArrayRows; i++) {
		RSE_MAN_GameObject::collisionArray[i] = new int[collisionArrayColumns];
		for (int e = 0; e < collisionArrayColumns; e++) {
			RSE_MAN_GameObject::collisionArray[i][e] = 0;
		}
	}
	RSE_MAN_GameObject::pObjLen = 1;
	RSE_MAN_GameObject::pObjPtr = 0;
	RSE_MAN_GameObject::pObjSize ++;
	RSE_MAN_GameObject::pObjectsArray = new RSE_GameObject*[RSE_MAN_GameObject::pObjLen];
	if (RSE_MAN_GameObject::CMAP_DEBUG) {
		RSE_MAN_GameObject::cmapDebugWindow = SDL_CreateWindow(
			"Collision Map Debug Screen",
			SDL_WINDOWPOS_UNDEFINED,
			SDL_WINDOWPOS_UNDEFINED,
			collisionArrayColumns * 3,
			collisionArrayRows * 3,
			SDL_WINDOW_ALWAYS_ON_TOP
		);
		if (RSE_MAN_GameObject::cmapDebugWindow != NULL) {
			RSE_MAN_GameObject::cmapDebugSurface = SDL_GetWindowSurface(RSE_MAN_GameObject::cmapDebugWindow);
			SDL_FillRect(RSE_MAN_GameObject::cmapDebugSurface, NULL, SDL_MapRGB(RSE_MAN_GameObject::cmapDebugSurface->format, 0x00, 0x00, 0x00));
			SDL_UpdateWindowSurface(RSE_MAN_GameObject::cmapDebugWindow);
		}
	}
}

void RSE_MAN_GameObject::updateAllObjects(SDL_Event* ptr_event) {
	
	RSE_MAN_GameObject::updateNumber++;

	RSE_MAN_GameObject::eventHandler->process(ptr_event);

	list<RSE_GameObject*>::iterator it;
	for (it = RSE_MAN_GameObject::objectsArray.begin(); it != RSE_MAN_GameObject::objectsArray.end(); it++) {
		RSE_GameObject* ptr_cur = *it;
		if ((ptr_cur->destoryOffScreen && !isVisibleOnScreen(ptr_cur)) || ptr_cur->garbage) {
			RSE_MAN_GameObject::garbageArray.push(ptr_cur);
		}
		else {
			ptr_cur->draw();
			ptr_cur->update();
		}
	}
	while (!RSE_MAN_GameObject::garbageArray.empty()) {
		RSE_GameObject* ptr_rem = RSE_MAN_GameObject::garbageArray.top();
		RSE_MAN_GameObject::garbageArray.pop();
		RSE_MAN_GameObject::objectsArray.remove(ptr_rem);
		delete ptr_rem;
	}
	RSE_Time* temp_timer = new RSE_Time();
	temp_timer->start();
	for (int i = 0; i < pObjLen; i++) {
		RSE_GameObject* ptr_cur = RSE_MAN_GameObject::pObjectsArray[i];
		if (ptr_cur == nullptr) {
			continue;
		}
		if ((ptr_cur->destoryOffScreen && !isVisibleOnScreen(ptr_cur)) || ptr_cur->garbage) {
			RSE_MAN_GameObject::garbageInexes.push(i);
		}
		else {
			ptr_cur->draw();
			ptr_cur->update();
		}
	}
	temp_timer->stop();
	//cout << "pObjUpdate: " << temp_timer->getTime().count() << "\n";
	delete temp_timer;
	while (!RSE_MAN_GameObject::garbageInexes.empty()) {
		int idx_rem = RSE_MAN_GameObject::garbageInexes.top();
		RSE_MAN_GameObject::garbageInexes.pop();
		delete RSE_MAN_GameObject::pObjectsArray[idx_rem];
		RSE_MAN_GameObject::pObjectsArray[idx_rem] = nullptr;
		RSE_MAN_GameObject::pObjSize--;
	}
	if (RSE_MAN_GameObject::CMAP_DEBUG && RSE_MAN_GameObject::cmapDebugWindow && RSE_MAN_GameObject::updateNumber % 50 == 0) {
		float collisionArrayRows = ceil(RSE_MAN_GameObject::SCREEN_HEIGHT / RSE_MAN_GameObject::SQUARE_SIZE);
		float collisionArrayColumns = ceil(RSE_MAN_GameObject::SCREEN_WIDTH / RSE_MAN_GameObject::SQUARE_SIZE);
		SDL_FillRect(RSE_MAN_GameObject::cmapDebugSurface, NULL, SDL_MapRGB(RSE_MAN_GameObject::cmapDebugSurface->format, 0x00, 0x00, 0x00));
		for (int y = 0; y < collisionArrayRows; y++) {
			for (int x = 0; x < collisionArrayColumns; x++) {
				int val = RSE_MAN_GameObject::collisionArray[y][x];
				if (val != 0) {
					SDL_Rect* r = new SDL_Rect();
					r->x = x*3;
					r->y = y*3;
					r->w = 3;
					r->h = 3;
					if ((y + x) % 2 == 0) {
						SDL_FillRect(RSE_MAN_GameObject::cmapDebugSurface, r, SDL_MapRGB(RSE_MAN_GameObject::cmapDebugSurface->format, 0xFF, 0xFF, 0xFF));
					}
					else {
						SDL_FillRect(RSE_MAN_GameObject::cmapDebugSurface, r, SDL_MapRGB(RSE_MAN_GameObject::cmapDebugSurface->format, 0xFF, 0x00, 0x00));
					}
					SDL_UpdateWindowSurface(RSE_MAN_GameObject::cmapDebugWindow);
					delete r;
				}
			}
		}
	}

}

bool RSE_MAN_GameObject::isVisibleOnScreen(RSE_GameObject* ptr_obj) {
	bool diag1 = RSE_MAN_GameObject::isPointOnScreen(ptr_obj->position->x, ptr_obj->position->y) || RSE_MAN_GameObject::isPointOnScreen(ptr_obj->position->x + ptr_obj->w, ptr_obj->position->y + ptr_obj->h);
	bool diag2 = RSE_MAN_GameObject::isPointOnScreen(ptr_obj->position->x + ptr_obj->w, ptr_obj->position->y) || RSE_MAN_GameObject::isPointOnScreen(ptr_obj->position->x, ptr_obj->position->y + ptr_obj->h);
	return diag1 || diag2;
}

bool RSE_MAN_GameObject::isPointOnScreen(float x, float y) {
	return x >= 0 && y >= 0 && x < RSE_MAN_GameObject::SCREEN_HEIGHT && y < RSE_MAN_GameObject::SCREEN_HEIGHT;
}

RSE_GameObject* RSE_MAN_GameObject::addGameObject(RSE_GameObject* ptr_obj) {
	RSE_MAN_GameObject::objectsArray.push_front(ptr_obj);
	return ptr_obj;
}

RSE_GameObject* RSE_MAN_GameObject::addPhysicsObject(RSE_GameObject* ptr_obj) {
	if (RSE_MAN_GameObject::pObjPtr == RSE_MAN_GameObject::pObjLen) {
		// if pointer is out of bounds of array, double array size
		RSE_GameObject **tempArr = new RSE_GameObject*[RSE_MAN_GameObject::pObjLen*2];
		for (int i = 0; i < RSE_MAN_GameObject::pObjLen; i++) {
			tempArr[i] = RSE_MAN_GameObject::pObjectsArray[i];
		}
		for (int i = pObjLen; i < pObjLen * 2; i++) {
			tempArr[i] = nullptr;
		}
		delete RSE_MAN_GameObject::pObjectsArray;
		RSE_MAN_GameObject::pObjLen *= 2;
		RSE_MAN_GameObject::pObjectsArray = tempArr;
	}
	ptr_obj->index = RSE_MAN_GameObject::pObjPtr + 1;
	RSE_MAN_GameObject::pObjectsArray[RSE_MAN_GameObject::pObjPtr] = ptr_obj;
	RSE_MAN_GameObject::pObjPtr++;
	cout << "Created New PhysicsObject in:[ " << RSE_MAN_GameObject::pObjLen << " ] as: [ "<< RSE_MAN_GameObject::pObjPtr<<" ]\n";
	return ptr_obj;
}

RSE_GameObject* RSE_MAN_GameObject::createGameObject(float x, float y, string imageId) {
	RSE_GameObject* ptr_n = new RSE_GameObject(x, y, imageId);
	RSE_MAN_GameObject::objectsArray.push_front(ptr_n);
	cout << "\ncreated new object at [ " << x << ", " << y << " ] with image id [ " << imageId << " ]\n";
	return ptr_n;
}

RSE_GameObject* RSE_MAN_GameObject::getGameObject(RSE_ID* id) {
	list<RSE_GameObject*>::iterator it;
	for (it = RSE_MAN_GameObject::objectsArray.begin(); it != RSE_MAN_GameObject::objectsArray.end(); it++) {
		RSE_GameObject* ptr_cur = *it;
		if (ptr_cur->id == id) {
			return ptr_cur;
		}
	}
	return nullptr;
}

