#include "stdafx.h"
#include "Sprite.h"

#include "Framework.h"

#include <SDL_image.h>

Sprite::Sprite(const char* path, int i_x /*= 0*/, int i_y /*= 0*/) {
	SDL_Surface* image = IMG_Load(path);
	texture = SDL_CreateTextureFromSurface(GetRenderer(), image);

	srcRect.w = image->w;
	srcRect.h = image->h;
	srcRect.x = 0;
	srcRect.y = 0;

	destRect.w = image->w;
	destRect.h = image->h;
	destRect.x = i_x;
	destRect.y = i_y;

	SDL_FreeSurface(image);
}

Sprite::Sprite(SDL_Surface* image, int i_x /*= 0*/, int i_y /*= 0*/) {
	texture = SDL_CreateTextureFromSurface(GetRenderer(), image);

	srcRect.w = image->w;
	srcRect.h = image->h;
	srcRect.x = 0;
	srcRect.y = 0;

	destRect.w = image->w;
	destRect.h = image->h;
	UpdatePosition(i_x, i_y);
}

Sprite::~Sprite() {
	SDL_DestroyTexture(texture);
}

void Sprite::UpdatePosition(int x, int y) {
	destRect.x = x + destRect.w / 2;
	destRect.y = y + destRect.h / 2;
}

void Sprite::Render() const {
	SDL_RenderCopy(GetRenderer(), texture, nullptr, &destRect);
	SDL_RenderPresent(GetRenderer());
}