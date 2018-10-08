#pragma once

#include "GameObject.h"

struct SDL_Surface;

class Bullet : public GameObject {
public:
	Bullet(Bullet&& another);
	Bullet& operator = (Bullet&& another);

	Bullet(SDL_Surface* image
		, double i_x, double i_y //appeared at (i_x, i_y)
		, double i_angle);

	int GetId() const { return id; }

	void Update(double sp = 1.) override;

private:
	void GeneratePosition(int i_window_w, int i_window_h) override {};

private:
	static int last_bullet_id;

	double alpha;

	int id;
};