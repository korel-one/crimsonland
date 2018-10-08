#include "stdafx.h"
#include "Enemy.h"

#include <Framework.h>

#include <iostream>

Enemy::Enemy(SDL_Surface* image) : GameObject(image) {}

void Enemy::_GeneratePosition(int map_w, int map_h, int R
	, int avatar_x, int avatar_y) {

	int range_w = map_w - GetWidth();
	int range_h = map_h - GetHeight();

	int pos_x = rand() % range_w;
	int pos_y = rand() % range_h;

	while (((avatar_x - pos_x)*(avatar_x - pos_x) +
		(avatar_y - pos_y)*(avatar_y - pos_y)) <= R * R) {

		pos_x = rand() % range_w;
		pos_y = rand() % range_h;
	}

	SetPositionX(pos_x);
	SetPositionY(pos_y);
}

void Enemy::GeneratePosition(int map_w, int map_h) {
	if (target_x == -1 || target_y == -1) {
		std::cerr << "ERROR! Avatar position is not specified yet" << std::endl;
		return;
	}

	// not closer than 200 px from (target_x, target_y)
	const int R = 200;

	_GeneratePosition(map_w, map_h, R, target_x, target_y);
}

// generates a number from 0.5 to 2.0
void Enemy::GenerateSpeed(double base_speed) {
	speed = (rand() % 1000 * 3.0 / 1000 + 1) / 2 * base_speed;
}

void Enemy::Update(double sp /*= 1*/) {
	double x = GetPositionX();
	double y = GetPositionY();

	auto alpha = atan2(1. * (target_y - y), 1. * (target_x - x));

	SetPositionX(x + speed * sp * cos(alpha));
	SetPositionY(y + speed * sp * sin(alpha));
}

bool Enemy::TouchedPlayer() const {
	return Intersect(GetPositionX(), GetPositionY(), GetWidth(), GetHeight()
		, target_x, target_y, target_w, target_h);
}