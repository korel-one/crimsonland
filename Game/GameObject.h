#pragma once

#include "Sprite.h"

#include <memory>
#include <set>

struct SDL_Surface;

class GameObject {
public:
	explicit GameObject(const char* path);
	explicit GameObject(SDL_Surface* image);

	int GetWidth() const { return sprite->GetWidth(); }
	int GetHeight() const { return sprite->GetHeight(); }

	void SetPositionX(double x) {
		this->x = x;
		sprite->SetPositionX(round(x));
	}

	void SetPositionY(double y) {
		this->y = y;
		sprite->SetPositionY(round(y));
	}

	double GetPositionX() const { return x; }
	double GetPositionY() const { return y; }

	void SetSpeed(double i_speed) {
		speed = i_speed;
	}

	double GetSpeed() const { return speed; }

	virtual void GeneratePosition(int i_window_w, int i_window_h) = 0;
	virtual void GenerateSpeed(double base_speed) { SetSpeed(base_speed); }
	virtual void Render() const;
	virtual void Update(double sp = 1.) = 0;

	virtual ~GameObject() {}

protected:
	std::unique_ptr<Sprite> sprite;

	int window_w = -1
		, window_h = -1;

	double speed = -1.;

	double x, y;
};