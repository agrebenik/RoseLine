#include "RSE_EventHandler.h"

RSE_EventHandler::RSE_EventHandler() {
}

 void RSE_EventHandler::process(SDL_Event* ptr_event) {
	SDL_Event event = *ptr_event;
	if (event.type == SDL_KEYDOWN || event.type == SDL_KEYUP) {
		int key;
		key = (int)event.key.keysym.sym;
		if (!keyRegistered(key)) {
			keyStates.insert(make_pair(key, false));
		}
		if (event.type == SDL_KEYDOWN && !keyStates[key]) {
			keyStates[key] = true;
		}
		if (event.type == SDL_KEYUP && keyStates[key]) {
			keyStates[key] = false;
		}
	}
	lastEvent = ptr_event;
}

 bool RSE_EventHandler::isKeyDown(int key) {
	 if (keyRegistered(key)) {
		 return keyStates[key];
	 }
	 return false;
}

bool RSE_EventHandler::keyRegistered(int key) {
	map<int, bool>::iterator it;
	for (it = keyStates.begin(); it != keyStates.end(); it++) {
		if (it->first == key) {
			return true;
		}
	}
	return false;
}

RSE_EventHandler::~RSE_EventHandler() {
	delete lastEvent;
}
