#include "RSE_MAN_Events.h"

#include <stack>

#define E RSE_MAN_Events::

using namespace std;

const Uint8* E keyboardState = nullptr;

SDL_Event** E lastEvents = new SDL_Event*[0];
SDL_Event** E currentEvents = new SDL_Event*[0];

unsigned int E lastEventLength = 0;
unsigned int E currentEventLength = 0;

int E update(SDL_Event* ptr_event) {
	stack<SDL_Event*> currentEventStack;
	if (ptr_event->type == SDL_QUIT) {
		return 1;
	}
	currentEventStack.push(ptr_event);
	SDL_Event load_event;
	int events = 1;
	while (SDL_PollEvent(&load_event) && events < EVENT_STACK_LIMIT) {
		if (load_event.type == SDL_QUIT) {
			return 1;
		}
		currentEventStack.push(&load_event);
		events += 1;
	}
	for (int i = 0; i < E currentEventLength; i++) {
		E currentEvents[i]->~SDL_Event();
	}
	E currentEvents = new SDL_Event*[currentEventStack.size()];
	int i = 0;
	while (!currentEventStack.empty()) {
		SDL_Event* ptr_currentEvent = currentEventStack.top();
		currentEventStack.pop();
		processEvent(ptr_currentEvent);
		E currentEvents[i] = ptr_currentEvent;
		i++;
	}
	E currentEventLength = i;
	return 0;
}

void E processEvent(SDL_Event* ptr_event) {
	switch (ptr_event->type) {
		case SDL_WINDOWEVENT:
			E handleWindowEvent((SDL_WindowEvent*)ptr_event);
			break;
		case SDL_KEYUP:
		case SDL_KEYDOWN:
			E handleKeyboardEvent((SDL_KeyboardEvent*)ptr_event);
			break;
		case SDL_USEREVENT:
			E handleUserEvent((SDL_UserEvent*)ptr_event);
			break;
	}
}

void E handleWindowEvent(SDL_WindowEvent* ptr_windowEvent) {
	
}


void E handleKeyboardEvent(SDL_KeyboardEvent* ptr_keyboardEvent) {
	const Uint8* ptr_keyboardState = SDL_GetKeyboardState(NULL);
	E keyboardState = ptr_keyboardState;
}

void E handleUserEvent(SDL_UserEvent* ptr_userEvent) {
	// add user event to user events stack
}

SDL_UserEvent** E getUserEvent(Sint32 code) {
	return nullptr;
}

bool E keyDown(ENM_Scancode scanCode) {
	return keyboardState[scanCode];
}

