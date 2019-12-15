#pragma once

#include <map>
#include <list>
#include <stack>
#include <string>

#include "RSE_ID.h"
#include "RSE_GameObject.h"
#include "RSE_EventHandler.h"

#include <SDL.h>

class RSE_MAN_GameObject
{
	static stack<RSE_GameObject*> garbageArray;
	static stack<int> garbageInexes;

public:

	// collision map debug
	static const bool CMAP_DEBUG = false;
	static SDL_Window *cmapDebugWindow;
	static SDL_Surface* cmapDebugSurface;

	static float SQUARE_SIZE;
	static int SCREEN_HEIGHT;
	static int SCREEN_WIDTH;
	
	static int** collisionArray;

	static int pObjPtr;
	static int pObjSize;
	static int pObjLen;

	static int updateNumber;

	static RSE_GameObject **pObjectsArray;

	static list<RSE_GameObject*> objectsArray;

	static RSE_EventHandler* eventHandler;

	static void Init(const int, const int);

	static void updateAllObjects(SDL_Event*);

	static bool isVisibleOnScreen(RSE_GameObject*);
	static bool isPointOnScreen(float x, float y);

	static RSE_GameObject* addGameObject(RSE_GameObject*);
	static RSE_GameObject* addPhysicsObject(RSE_GameObject*);
	static RSE_GameObject* createGameObject(float, float, string);
	static RSE_GameObject* getGameObject(RSE_ID*);

};