// Framework3.cpp : Defines the exported functions for the DLL application.
//

#include "stdafx.h"
#include "Framework.h"
#include "Sprite.h"

#include <SDL_image.h>

static SDL_Renderer* gRenderer = nullptr;

SDL_Renderer* GetRenderer(SDL_Window* window /*= nullptr*/) { 
	if (window) {
		gRenderer = SDL_CreateRenderer(window, -1, 0);
	}
	return gRenderer; 
}

static bool gRestartGame = true;
bool RestartGame() { return gRestartGame; }
void SetRestartGame(bool restart) { 
	gRestartGame = restart;
}

//------------------------------------------------------------------
IMG_LOAD::IMG_LOAD(const char* path) {
	image = IMG_Load(path);
}

IMG_LOAD::~IMG_LOAD() {
	SDL_FreeSurface(image);
}

//------------------------------------------------------------------
Sprite* createSprite(const char* path) {
	return new Sprite(path);
}

Sprite* createSprite(SDL_Surface* image) {
	return new Sprite(image);
}

void drawSprite(Sprite* sprite, int x, int y) {
	auto texture = sprite->GetTexture();

	SDL_Rect destRect;
	destRect.x = x;
	destRect.y = y;
	destRect.w = sprite->GetWidth();
	destRect.h = sprite->GetHeight();

	SDL_RenderCopy(gRenderer, texture, nullptr, &destRect);
	SDL_RenderPresent(gRenderer);
}

void getSpriteSize(Sprite* s, int& w, int &h) {
	w = s->GetWidth();
	h = s->GetHeight();
}

void destroySprite(Sprite* s) {
	delete s;
	s = nullptr;
}

void drawTestBackground() {
	//TODO: 
}

void getScreenSize(int& w, int &h) {
	SDL_DisplayMode display_mode;
	if (SDL_GetDesktopDisplayMode(0, &display_mode) != 0) {
		SDL_Log("SDL_GetDesktopDisplayMode failed: %s", SDL_GetError());
	}

	int w1 = display_mode.w;
	int h1 = display_mode.h;

	//or

	int w2 = ::GetSystemMetrics(SM_CXSCREEN);
	int h2 = ::GetSystemMetrics(SM_CYSCREEN);

	w = w2;
	h = h2;
}

unsigned int getTickCount() {
	//TODO:
	return 0; 
}

void showCursor(bool bShow) {
	//TODO:
}

bool Intersect(double x1, double y1, int w1, int h1
	, double x2, double y2, int w2, int h2) {

	bool x_intersect = (x1 >= x2 && x1 <= (x2 + w2)) ||
		((x1 + w1) >= x2 && ((x1 + w1) <= (x2 + w2)));

	bool y_intersect = (y1 >= y2 && y1 <= (y2 + h2)) ||
		((y1 + h1) >= y2 && (y1 + h1) <= (y2 + h2));

	return x_intersect && y_intersect;
}

int run(Framework* p_framework) {
	bool quit = !p_framework->Init();
	if (quit) {
		gRestartGame = false;
		return 1;
	}

	bool mouse_pressed = false;

	SDL_Event event;
	while (!quit) {
		SDL_Delay(20);
		SDL_PollEvent(&event);

		switch (event.type) {
			case SDL_QUIT:
				quit = true;
				gRestartGame = false;
				break;

			// pressed
			case SDL_KEYDOWN:
				switch (event.key.keysym.sym)
				{
				case SDLK_LEFT:
					p_framework->onKeyPressed(FRKey::LEFT);
					break;
				case SDLK_RIGHT:
					p_framework->onKeyPressed(FRKey::RIGHT);
					break;
				case SDLK_UP:
					p_framework->onKeyPressed(FRKey::UP);
					break;
				case SDLK_DOWN:
					p_framework->onKeyPressed(FRKey::DOWN);
					break;
				}
				break;

			// released
			case SDL_KEYUP:
				switch (event.key.keysym.sym)
				{
				case SDLK_LEFT:
					p_framework->onKeyReleased(FRKey::LEFT);
					break;
				case SDLK_RIGHT:
					p_framework->onKeyReleased(FRKey::RIGHT);
					break;
				case SDLK_UP:
					p_framework->onKeyReleased(FRKey::UP);
					break;
				case SDLK_DOWN:
					p_framework->onKeyReleased(FRKey::DOWN);
					break;
				}
				break;

			// mouse move
			case SDL_MOUSEMOTION:
				p_framework->onMouseMove(event.motion.x, event.motion.y
					, event.motion.xrel, event.motion.yrel);

				break;

			case SDL_MOUSEBUTTONUP:
				if (mouse_pressed) {
					mouse_pressed = false;

					if (event.button.button == SDL_BUTTON_LEFT) {
						p_framework->onMouseButtonClick(FRMouseButton::LEFT, !mouse_pressed);
					}
				}
				break;
			case SDL_MOUSEBUTTONDOWN:
				if (!mouse_pressed) {
					mouse_pressed = true;

					if (event.button.button == SDL_BUTTON_LEFT) {
						p_framework->onMouseButtonClick(FRMouseButton::LEFT, !mouse_pressed);
					}
				}
				break;
		}

		if (quit)
			break;
		else
			quit = p_framework->Tick();
	}
	p_framework->Close();
	return 0;
}