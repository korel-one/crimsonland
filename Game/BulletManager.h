#pragma once

#include "Bullet.h"

#include <Framework.h>

#include <functional>
#include <memory>
#include <map>


struct IMG_LOAD;

class BulletManager {
public:
	BulletManager(const char* path, int i_max_ammo);

	void GenerateBullet(double pos_x, double pos_y, double angle);

	void RenderAll();
	void UpdateAll();

	const Bullet* FindAnyOf(std::function<bool(const GameObject&)> func) const;
	void RemoveById(int id) { bullets.erase(id); }

private:
	int max_ammo;
	std::unique_ptr<IMG_LOAD> image_loader;

	using TBullets = std::map<int, std::unique_ptr<Bullet>>;
	TBullets bullets;
};