#include "stdafx.h"
#include "EnemyManager.h"
#include "Enemy.h"

#include <Framework.h>

#include <SDL_image.h>

#include <algorithm>
#include <iomanip>
#include <iostream>

#include <math.h>
#include <time.h>

EnemyManager::EnemyManager(int i_num_enemies)
	: num_enemies(i_num_enemies) {
}

void EnemyManager::GenerateEnemies(const char* path
	, int window_w, int window_h
	, int target_x, int target_y
	, int target_w, int target_h) {

	Clear();
	if (!image_loader) {
		image_loader = std::make_unique<IMG_LOAD>(path);
	}

	// initialize random seed
	srand(1);

	for (int i = 0; i < num_enemies; ++i) {

		_enemies.emplace_back(std::make_unique<Enemy>(image_loader->image));
		_enemies.back()->SetTargetSize(target_w, target_h);
		_enemies.back()->UpdateTargetPos(target_x, target_y);

		_enemies.back()->GeneratePosition(window_w, window_h);
		while (IntersectAny(*_enemies.back())) {
			_enemies.back()->GeneratePosition(window_w, window_h);
		}
		_enemies.back()->GenerateSpeed(0.3);
	}

}

void EnemyManager::RenderAll() {

	for (auto& e : _enemies) {
		e->Render();
	}
}

void EnemyManager::UpdateAll() {
	for (auto& e : _enemies) {
		e->Update();

		if (IntersectAny(*e))
			e->Update(-1);
	}
}

void EnemyManager::Clear() {
	_enemies = TEnemies();
	_enemies.reserve(num_enemies);
}

void EnemyManager::PlayerMoved(int x, int y) {
	for (auto& e : _enemies) {
		e->UpdateTargetPos(x, y);
	}
}

Enemy* EnemyManager::IntersectAny(const GameObject& e) const {
	auto it_enemy = std::find_if(_enemies.begin(), _enemies.end(), [&](const TEnemies::value_type& p_enemy) {
		if (p_enemy.get() == &e)
			return false;

		return Intersect(e.GetPositionX(), e.GetPositionY(), e.GetWidth(), e.GetHeight()
			, p_enemy->GetPositionX(), p_enemy->GetPositionY(), p_enemy->GetWidth(), p_enemy->GetHeight());
	});

	if (it_enemy != _enemies.end()) {
		return it_enemy->get();
	}
	return nullptr;
}

bool EnemyManager::AnyTouchedPlayer() const {
	return std::any_of(_enemies.begin(), _enemies.end(), [](const TEnemies::value_type& enemy) {
		return enemy->TouchedPlayer();
	});
}

void EnemyManager::RemoveEnemy(const Enemy* p_enemy) {
	auto it_res = std::find_if(_enemies.begin(), _enemies.end(), [&p_enemy](const TEnemies::value_type& ip_enemy) {
		return p_enemy == ip_enemy.get();
	});

	if (it_res != _enemies.end()) {
		_enemies.erase(it_res);
	}
}