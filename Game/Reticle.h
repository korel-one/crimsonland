#pragma once

#include <SDL.h>

class Reticle {
public:
	explicit Reticle(const char* path);
	~Reticle();

	void UpdatePosition(int i_x, int i_y);

	int GetPositionX() const;
	int GetPositionY() const;

private:
	SDL_Cursor* cursor = nullptr;
	int x = -1, y = -1;
};