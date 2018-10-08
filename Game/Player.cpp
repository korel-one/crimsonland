#include "stdafx.h"

#include "Player.h"
#include "BulletManager.h"
#include "Sprite.h"

Player::Player(const char* path)
	: GameObject(path)
{}

void Player::GeneratePosition(int window_w, int window_h) {
	SetPositionX(window_w / 2.);
	SetPositionY(window_h / 2.);
}

void Player::Update(double sp /*= 1*/) {
	bullet_manager->UpdateAll();
}

void Player::Render() const {
	GameObject::Render();
	bullet_manager->RenderAll();
}

void Player::Charge(const char* path, int i_max_ammo) {
	bullet_manager = std::make_unique<BulletManager>(path, i_max_ammo);
}

void Player::Shoot(double reticle_x, double reticle_y) {
	auto alpha = atan2(1.*(reticle_y - y), 1.*(reticle_x - x));
	bullet_manager->GenerateBullet(x + GetWidth()/2., y + GetHeight()/2., alpha);
}

const Bullet* Player::AnyBullet(std::function<bool(const GameObject&)> func) const {
	return bullet_manager->FindAnyOf(func);
}


void Player::HitUpdate(int bullet_id) {
	bullet_manager->RemoveById(bullet_id);
}