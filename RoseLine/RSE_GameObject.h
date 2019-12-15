#pragma once

#include <SDL.h>

#include <string>

#include "RSE_ID.h"
#include "RSE_Point.h"

class RSE_GameObject
{
	int updates;
	SDL_Texture* currentTexture;
	SDL_Surface* currentSurface;
public:

	int index = -1;

	RSE_Point* position;
	RSE_ID* id;

	float w, h;
	float opacity = 255.00f;
	bool visible = true;
	bool garbage = false;
	bool destoryOffScreen = false;
	float angle;
	string imageId;

	virtual int draw();
	virtual int update();
	
	void shift(float, float);

	void setImage(string);

	bool operator==(const RSE_GameObject*);
	
	RSE_GameObject(float, float);
	RSE_GameObject(float, float, string);
	virtual ~RSE_GameObject();
};