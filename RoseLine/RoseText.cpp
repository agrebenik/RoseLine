
#include <SDL.h>

#include <stdio.h>
#include <iostream>

#include "RSE_MAN_Events.h"
#include "RSE_MAN_Resource.h"
#include "RSE_MAN_GameObject.h"

#include "RSE_PhysicsObject.h"

#define Events RSE_MAN_Events::
#define Resources RSE_MAN_Resource::
#define Objects RSE_MAN_GameObject::

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

using namespace std;

int main(int argc, char* args[]) {
	SDL_Window* window = NULL;
	SDL_Renderer* renderer = NULL;
	SDL_Surface* screenSurface = NULL;
	SDL_Event event;

	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		return 3;
	}

	if (SDL_Init(SDL_INIT_AUDIO) < 0) {
		return 3;
	}

	if (SDL_CreateWindowAndRenderer(SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_RESIZABLE, &window, &renderer)) {
		return 3;
	}
	
	Resources Init(window, renderer);
	Objects Init(SCREEN_WIDTH, SCREEN_HEIGHT);
	Resources loadSurface("test1", "C:\\Users\\usagi\\Desktop\\RoseAssets\\test1.png");
	Resources loadSurface("ball", "C:\\Users\\usagi\\Desktop\\RoseAssets\\ball.png");
	Objects createGameObject(0, 0, "ball");
	for (int i = 0; i < 6; i++) {
		RSE_PhysicsObject* obj = new RSE_PhysicsObject(100.0 + i * 11, 100.0, "ball");
		obj->bump((i+1)/10.0f, (6-i)/10.0f);
		obj->rigid = false;
		obj->w = 10;
		obj->h = 10;
		RSE_MAN_GameObject::addPhysicsObject(obj);
	}
	RSE_PhysicsObject* lb = new RSE_PhysicsObject(50, 250, "test1");
	RSE_PhysicsObject* rb = new RSE_PhysicsObject(600, 250, "test1");
	RSE_PhysicsObject* bb = new RSE_PhysicsObject(300, 350, "test1");
	RSE_PhysicsObject* bb2 = new RSE_PhysicsObject(350, 250, "test1");
	lb->h = 500;
	rb->h = 500;
	bb->w = 500;
	bb2->w = 500;
	Objects addPhysicsObject(lb);
	lb->setCollision(); 
	Objects addPhysicsObject(rb);
	rb->setCollision();
	Objects addPhysicsObject(bb);
	bb->setCollision();
	Objects addPhysicsObject(bb2);
	bb2->setCollision();


	int quit = false;

	while (!quit) {
		SDL_PollEvent(&event);

		if (event.type == SDL_QUIT) {
			break;
		}

		SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0x00);
		SDL_RenderClear(renderer);

		quit = RSE_MAN_Events::update(&event);

		RSE_MAN_GameObject::updateAllObjects(&event);

		SDL_RenderPresent(renderer);
	}

	SDL_DestroyWindow(window);
	SDL_Quit();
	return 0;
}