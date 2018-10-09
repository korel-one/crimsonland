#include "stdafx.h"
#include "Bullet.h"

#include <SDL.h>

int Bullet::last_bullet_id;

Bullet::Bullet(SDL_Surface* image
	, double i_x, double i_y //appeared at (i_x, i_y)
	, double i_angle)
	: GameObject(image)
	, alpha(i_angle)
{
	SetPositionX(i_x);
	SetPositionY(i_y);

	id = ++last_bullet_id;
	SetSpeed(2.5);
}

void Bullet::Update(double sp /*= 1*/) {
	SetPositionX(GetPositionX() + speed * cos(alpha));
	SetPositionY(GetPositionY() + speed * sin(alpha));
}