#include "stdafx.h"
#include "BulletManager.h"

#include <algorithm>
#include <iostream>

BulletManager::BulletManager(const char* path, int i_max_ammo)
	:max_ammo(i_max_ammo) 
{
	image_loader = std::make_unique<IMG_LOAD>(path);
}

void BulletManager::GenerateBullet(double pos_x, double pos_y, double angle) {

	if (bullets.size() == max_ammo) {
		bullets.erase(bullets.begin()->second->GetId());
	}
	auto bullet = std::make_unique<Bullet>(image_loader->image, pos_x, pos_y, angle);
	bullets[bullet->GetId()] = std::move(bullet);
}

void BulletManager::RenderAll() {
	for (auto it = bullets.begin(); it != bullets.end(); ++it) {
		it->second->Render();
	}
}

void BulletManager::UpdateAll() {
	for (auto it = bullets.begin(); it != bullets.end(); ++it) {
		it->second->Update();
	}
}

const Bullet* BulletManager::FindAnyOf(std::function<bool(const GameObject&)> func) const {
	auto it_bullet = std::find_if(bullets.begin(), bullets.end(), [&](const TBullets::value_type& key_value) {
		return func(*key_value.second);
	});

	if (it_bullet != bullets.end()) {
		return it_bullet->second.get();
	}
	return nullptr;
}