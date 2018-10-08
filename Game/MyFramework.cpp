#include "stdafx.h"
#include "MyFramework.h"

#include "Bullet.h"
#include "EnemyManager.h"
#include "Enemy.h"
#include "Player.h"
#include "Reticle.h"

#include <Windows.h>
#include <iostream>

#include <SDL.h>
#include <SDL_image.h>

SDL_Window* gWindow = nullptr;
SDL_Renderer* gRenderer = nullptr;


MyFramework::MyFramework(int num_enemies /*= 100*/
	, int i_max_ammo /*= 3*/
	, int window_w /*= -1*/
	, int window_h /*= -1*/)
	: Framework()
	, window_size_w(window_w)
	, window_size_h(window_h)
	, max_ammo(i_max_ammo)
{
	fullscreen = (window_size_h == -1 && window_size_w == -1);
	if (fullscreen) {
		window_size_w = ::GetSystemMetrics(SM_CXSCREEN);
		window_size_h = ::GetSystemMetrics(SM_CYSCREEN);

		//getScreenSize(window_size_w, window_size_h);
	}

	enemy_manager = std::make_unique<EnemyManager>(num_enemies);
}

void MyFramework::PreInit(int& width, int& height, bool& fullscreen)
{
	width = window_size_w;
	height = window_size_h;
	fullscreen = this->fullscreen;
}

bool MyFramework::Init() {
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
		return false;
	}

	if (!IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG)) {
		return false;
	}

	int flags = SDL_WINDOW_SHOWN;
	if (fullscreen) {
		flags |= SDL_WINDOW_FULLSCREEN_DESKTOP;//SDL_WINDOW_FULLSCREEN;
	}

	window_size_w = 1024;
	window_size_h = 680;

	gWindow = SDL_CreateWindow("Crimsonland",
		SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, window_size_w, window_size_h, SDL_WINDOW_SHOWN);

	gRenderer = GetRenderer(gWindow);
	SDL_SetRenderDrawColor(gRenderer, 0, 255, 0, 255);

	auto player_path = "D:\\interview\\dragonlake\\data\\avatar.jpg";
	auto enemy_path = "D:\\interview\\dragonlake\\data\\enemy.png";
	auto cursor_path = "D:\\interview\\dragonlake\\data\\circle.tga";
	auto bullet_path = "D:\\interview\\dragonlake\\data\\bullet.png";

	player = std::make_unique<Player>(player_path);
	player->GeneratePosition(window_size_w, window_size_h);
	player->GenerateSpeed(1.);
	player->Charge(bullet_path, max_ammo);

	enemy_manager->GenerateEnemies(enemy_path, window_size_w, window_size_h
		, player->GetPositionX(), player->GetPositionY()
		, player->GetWidth(), player->GetHeight());

	reticle = std::make_unique<Reticle>(cursor_path);

	return true;
}

void MyFramework::Close() {
	SDL_DestroyRenderer(gRenderer);
	SDL_DestroyWindow(gWindow);

	gRenderer = nullptr;
	gWindow = nullptr;

	IMG_Quit();
	SDL_Quit();
}

void MyFramework::UpdateKill() {

	Enemy* p_enemy = nullptr;
	auto p_bullet = player->AnyBullet([em = enemy_manager.get(), &p_enemy](const GameObject& game_object) ->bool {
		p_enemy = em->IntersectAny(game_object);
		return p_enemy != nullptr;
	});

	if (p_bullet && p_enemy) {

		//remove bullet, remove enemy
		player->HitUpdate(p_bullet->GetId());
		enemy_manager->RemoveEnemy(p_enemy);
	}
}

bool MyFramework::Tick() {
	SDL_RenderClear(gRenderer);

	enemy_manager->UpdateAll();
	enemy_manager->RenderAll();

	player->Update();
	player->Render();

	UpdateKill();

	if (enemy_manager->AnyTouchedPlayer()) {
		SetRestartGame(true);
		return true;
	}

	drawTestBackground();
	return false;
}

void MyFramework::onMouseMove(int x, int y, int xrelative, int yrelative) {
	reticle->UpdatePosition(x, y);
}

void MyFramework::onMouseButtonClick(FRMouseButton button, bool isReleased) {
	if (button == FRMouseButton::LEFT && !isReleased) {
		player->Shoot(reticle->GetPositionX(), reticle->GetPositionY());
	}
}

void MyFramework::onKeyPressed(FRKey k) {
	if (k == FRKey::LEFT) {
		player->SetPositionX(player->GetPositionX() - player->GetSpeed());
	}
	else if (k == FRKey::RIGHT) {
		player->SetPositionX(player->GetPositionX() + player->GetSpeed());
	}
	else if (k == FRKey::UP) {
		player->SetPositionY(player->GetPositionY() - player->GetSpeed());
	}
	else {
		player->SetPositionY(player->GetPositionY() + player->GetSpeed());
	}
	enemy_manager->PlayerMoved(player->GetPositionX(), player->GetPositionY());
}

void MyFramework::onKeyReleased(FRKey /*k*/) {}