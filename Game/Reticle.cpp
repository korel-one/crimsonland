#include "stdafx.h"
#include "Reticle.h"

#include <SDL.h>
#include <SDL_image.h>

#include <iostream>

Reticle::Reticle(const char* path) {
	SDL_RWops* rwop = SDL_RWFromFile(path, "rb");
	SDL_Surface* surface = IMG_LoadTGA_RW(rwop);
	SDL_RWclose(rwop);

	cursor = SDL_CreateColorCursor(surface, 0, 0);
	SDL_SetCursor(cursor);

	SDL_FreeSurface(surface);
}

Reticle::~Reticle() {
	SDL_FreeCursor(cursor);
}

void Reticle::UpdatePosition(int i_x, int i_y) {
	x = i_x;
	y = i_y;
}

int Reticle::GetPositionX() const { return x; }
int Reticle::GetPositionY() const { return y; }