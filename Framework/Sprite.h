#pragma once

#include "DllImport.h"

#include <SDL.h>

class FRAMEWORK_API Sprite {
public:

	Sprite(const char* path, int i_x = 0, int i_y = 0);
	Sprite(SDL_Surface* image, int i_x = 0, int i_y = 0);

	Sprite(Sprite&& source);
	Sprite& operator=(Sprite&& source);

	Sprite(const Sprite&) = delete;
	Sprite& operator=(const Sprite&) = delete;

	~Sprite();

	void UpdatePosition(int x, int y);
	void Render() const;

	int GetWidth() const { return srcRect.w; }
	int GetHeight() const { return srcRect.h; }

	int GetX() const { return destRect.x; }
	int GetY() const { return destRect.y; }

	void SetPositionX(int x) { destRect.x = x; }
	void SetPositionY(int y) { destRect.y = y; }

	SDL_Texture* GetTexture() const { return texture; }

private:
	SDL_Texture * texture = nullptr;

	SDL_Rect srcRect, destRect;
};