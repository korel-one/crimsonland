#pragma once

#include "GameObject.h"

#include <functional>
#include <memory>

class BulletManager;
class Bullet;

class Player : public GameObject {
public:
	explicit Player(const char* path);

	void GeneratePosition(int window_w, int window_h) override;
	void Update(double sp = 1) override;
	void Render() const override;

	void Charge(const char* path, int i_max_ammo);

	void Shoot(double reticle_x, double reticle_y);

	const Bullet* AnyBullet(std::function<bool(const GameObject&)> func) const;
	void HitUpdate(int bullet_id);

private:
	std::unique_ptr<BulletManager> bullet_manager;
};