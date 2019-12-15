
#include "RSE_GameObject.h"
#include "RSE_MAN_Resource.h"

#include <iostream>

using namespace std;

RSE_GameObject::RSE_GameObject(float x, float y) {
	position = new RSE_Point(x, y);
	id = new RSE_ID();
	angle = 0;
}

RSE_GameObject::RSE_GameObject(float x, float y, string imageId) {
	position = new RSE_Point(x, y);
	id = new RSE_ID();
	angle = 0;
	setImage(imageId);
	this->imageId = imageId;
}

void RSE_GameObject::shift(float dx, float dy) {
	position->x += dx;
	position->y += dy;
}

void RSE_GameObject::setImage(string imageId) {
	if (RSE_MAN_Resource::surfaceExists(imageId)) {
		cout << "GameObject image set to [ " << imageId << " ]" << endl;
		SDL_Surface* surface = RSE_MAN_Resource::getSurface(imageId);
		currentSurface = surface;
		w = currentSurface->w;
		h = currentSurface->h;
		currentTexture = SDL_CreateTextureFromSurface(RSE_MAN_Resource::renderer, currentSurface);
	}
	else {
		// surface does not exist in manager, throw error
		string msg = string("Failed to create game object: surface with id [ ") + imageId + string(" ] does not exist.");
		throw invalid_argument(msg);
	}
}

int RSE_GameObject::draw() {
	if (visible) {
		SDL_Rect* dr = new SDL_Rect();
		SDL_Point* center = new SDL_Point();
		center->x = w / 2.0;
		center->y = h / 2.0;
		dr->x = position->x - w / 2.0;
		dr->y = position->y - h / 2.0;
		dr->w = w;
		dr->h = h;
		SDL_SetTextureAlphaMod(currentTexture, opacity);
		SDL_RenderCopyEx(RSE_MAN_Resource::renderer, currentTexture, NULL, dr, angle, center, SDL_FLIP_NONE);
		delete dr;
		delete center;
	}
	return 0;
}

int RSE_GameObject::update() {
	return 0;
}

bool RSE_GameObject::operator==(const RSE_GameObject* other) {
	return this->id == other->id;
}

RSE_GameObject::~RSE_GameObject() {
	SDL_DestroyTexture(currentTexture); // CCP ( clear created pointer )
	delete position; // CCP 
	delete id;
}