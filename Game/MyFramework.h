#pragma once

#include <Framework.h>

#include <memory>

class EnemyManager;
class Reticle;
class Player;

struct SDL_Window;
extern SDL_Window* gWindow;

/* Test Framework realization */
class MyFramework : public Framework {

public:
	MyFramework(int num_enemies = 100, int i_max_ammo = 3, int window_w = -1, int window_h = -1);
	void PreInit(int& width, int& height, bool& fullscreen) override;

	bool Init() override;
	void Close() override;
	bool Tick() override;

	void onMouseMove(int x, int y, int xrelative, int yrelative) override;
	void onMouseButtonClick(FRMouseButton button, bool isReleased) override;

	void onKeyPressed(FRKey k) override;
	void onKeyReleased(FRKey k) override;

private:
	void UpdateKill();

private:
	std::unique_ptr<EnemyManager> enemy_manager;
	std::unique_ptr<Player> player;
	std::unique_ptr<Reticle> reticle;

	bool fullscreen;
	int window_size_w
		, window_size_h;

	int max_ammo;

	bool mouse_selection = false;
};