#pragma once

#include <SDL.h>
#include <map>

using namespace std;

class RSE_EventHandler
{
	SDL_Event* lastEvent;
	map<int, bool> keyStates;
public:

	virtual void process(SDL_Event*);

	bool isKeyDown(int);
	bool keyRegistered(int);

	RSE_EventHandler();
	~RSE_EventHandler();
};

