#pragma once

#pragma once

#include "DllImport.h"

// Bonus for any found bugs in the framework!

class Sprite;
struct SDL_Surface;

FRAMEWORK_API Sprite* createSprite(const char* path);
FRAMEWORK_API Sprite* createSprite(SDL_Surface* image);

FRAMEWORK_API void drawSprite(Sprite*, int x, int y);
FRAMEWORK_API void getSpriteSize(Sprite* s, int& w, int &h);
FRAMEWORK_API void destroySprite(Sprite* s);

FRAMEWORK_API void drawTestBackground();

FRAMEWORK_API void getScreenSize(int& w, int &h);

// Get the number of milliseconds since library initialization.
FRAMEWORK_API unsigned int getTickCount();

FRAMEWORK_API void showCursor(bool bShow);

enum class FRKey {
	RIGHT,
	LEFT,
	DOWN,
	UP,
	COUNT
};

enum class FRMouseButton {
	LEFT,
	MIDDLE,
	RIGHT,
	COUNT
};

class FRAMEWORK_API Framework {
public:

	// no function calls are available here, this function shuld only return width, height and fullscreen values
	virtual void PreInit(int& width, int& height, bool& fullscreen) = 0;

	// return : true - ok, false - failed, application will exit
	virtual bool Init() = 0;

	virtual void Close() = 0;

	// return value: if true will exit the application
	virtual bool Tick() = 0;

	// param: xrel, yrel: The relative motion in the X/Y direction 
	// param: x, y : coordinate, relative to window
	virtual void onMouseMove(int x, int y, int xrelative, int yrelative) = 0;

	virtual void onMouseButtonClick(FRMouseButton button, bool isReleased) = 0;

	virtual void onKeyPressed(FRKey k) = 0;

	virtual void onKeyReleased(FRKey k) = 0;

	virtual ~Framework() {};
};

FRAMEWORK_API bool Intersect(double x1, double y1, int w1, int h1
	, double x2, double y2, int w2, int h2);

FRAMEWORK_API int run(Framework*);

struct SDL_Renderer;
struct SDL_Window;

FRAMEWORK_API SDL_Renderer* GetRenderer(SDL_Window* window = nullptr);
FRAMEWORK_API bool RestartGame();
FRAMEWORK_API void SetRestartGame(bool restart);

struct FRAMEWORK_API IMG_LOAD {
	explicit IMG_LOAD(const char* path);
	~IMG_LOAD();

	SDL_Surface* image = nullptr;
};