#pragma once

#include "GameObject.h"

class Enemy
	: public GameObject {

public:
	explicit Enemy(SDL_Surface* image);

	void GeneratePosition(int window_w, int window_h) override;
	void GenerateSpeed(double base_speed) override;

	void Update(double sp = 1) override;

	bool TouchedPlayer() const;

	void SetTargetSize(int i_w, int i_h) {
		target_w = i_w;
		target_h = i_h;
	}

	void UpdateTargetPos(double i_x, double i_y) {
		target_x = i_x;
		target_y = i_y;
	}

private:
	void _GeneratePosition(int map_w, int map_h, int R, int avarat_w, int avatar_h);

private:
	double target_x = -1., target_y = -1.;
	int target_w = -1, target_h = -1;
};