#pragma once

#include <SDL.h>

#include <map>
#include <string>

using namespace std;

class RSE_Audio
{
private:
	Uint8 * audioPos;
	Uint32 audioLen;
public:
	Uint32 wavLength; 
	Uint8 *wavBuffer; 
	SDL_AudioSpec wavSpec; 
	RSE_Audio();
	void playAudio(string);
	void stopAudio();
	~RSE_Audio();
};

