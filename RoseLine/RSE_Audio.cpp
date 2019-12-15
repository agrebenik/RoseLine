#include "RSE_Audio.h"



RSE_Audio::RSE_Audio() { }

void RSE_Audio::playAudio(string path) {
	if (SDL_LoadWAV(path.c_str(), &wavSpec, &wavBuffer, &wavLength) == NULL) {
		string etext = "Could not load wav " + path;
		throw new exception(etext.c_str());
	}

}
void RSE_Audio::stopAudio() {

}

RSE_Audio::~RSE_Audio() { }
