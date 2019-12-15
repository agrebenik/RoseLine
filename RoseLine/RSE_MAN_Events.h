#pragma once

#include <SDL.h>

#include <map>

#include "ENM_Scancode.h"

class RSE_MAN_Events
{
private: 
	static const Uint8* keyboardState;
	static void processEvent(SDL_Event*);
	
	static void handleWindowEvent(SDL_WindowEvent*);
	static void handleKeyboardEvent(SDL_KeyboardEvent*);
	static void handleUserEvent(SDL_UserEvent*);
public:
	static const int EVENT_STACK_LIMIT = 20;

	static unsigned int lastEventLength;
	static unsigned int currentEventLength;
	static SDL_Event** lastEvents;
	static SDL_Event** currentEvents;

	static bool keyDown(ENM_Scancode);

	static SDL_UserEvent** getUserEvent(Sint32);

	static int update(SDL_Event*);
};

