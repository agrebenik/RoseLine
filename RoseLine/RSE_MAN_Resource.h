#pragma once

#include <map>
#include <string>
#include <SDL.h>

using namespace std;

class RSE_MAN_Resource
{
private:
	static map<string, SDL_Texture*> _textures;
	static map<string, SDL_Surface*> _surfaces;
public:
	static SDL_Surface* screenSurface;
	static SDL_Window* window;
	static SDL_Renderer* renderer;
	static void Init(SDL_Window*, SDL_Renderer*);
	static void setWindowSurface(SDL_Window*);
	static SDL_Surface* loadSurface(string, string);
	static SDL_Surface* getSurface(string);
	static bool surfaceExists(string);
};