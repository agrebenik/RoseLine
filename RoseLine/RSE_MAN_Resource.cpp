
#include <map>
#include <SDL.h>
#include <string>
#include <iostream>
#include <SDL_image.h>

#include "RSE_MAN_Resource.h"


map<string, SDL_Texture*> RSE_MAN_Resource::_textures;
map<string, SDL_Surface*> RSE_MAN_Resource::_surfaces;

SDL_Surface* RSE_MAN_Resource::screenSurface;
SDL_Window* RSE_MAN_Resource::window;
SDL_Renderer* RSE_MAN_Resource::renderer;

void RSE_MAN_Resource::Init(SDL_Window* ptr_window, SDL_Renderer* ptr_renderer) {
	RSE_MAN_Resource::screenSurface = SDL_GetWindowSurface(ptr_window);
	RSE_MAN_Resource::window = ptr_window;
	RSE_MAN_Resource::renderer = ptr_renderer;
}

void RSE_MAN_Resource::setWindowSurface(SDL_Window* ptr_window) {
	RSE_MAN_Resource::screenSurface = SDL_GetWindowSurface(ptr_window);
}

SDL_Surface* RSE_MAN_Resource::loadSurface(string id, string path) {
	SDL_Surface* loadedSurface = IMG_Load(path.c_str());
	if (loadedSurface == NULL) {
		printf("Unable to load image %s! SDL_image Error: \n\t%s", path.c_str(), IMG_GetError());
		return nullptr;
	}
	RSE_MAN_Resource::_surfaces.insert(make_pair(id, loadedSurface));
	string msg = string("Loaded surface [ ") + id + string(" ] from [ ") + path + string(" ].");
	cout << msg << '\n';
	return loadedSurface;
}

SDL_Surface* RSE_MAN_Resource::getSurface(string id) {
	return RSE_MAN_Resource::_surfaces.find(id)->second;
}

bool RSE_MAN_Resource::surfaceExists(string id) {
	map<string, SDL_Surface*>::iterator it;
	for (it = RSE_MAN_Resource::_surfaces.begin(); it != _surfaces.end(); it++) {
		if (it->first == id) {
			return true;
		}
	}
	return false;
}
