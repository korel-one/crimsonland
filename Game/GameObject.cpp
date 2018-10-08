#include "stdafx.h"
#include "GameObject.h"

#include <Framework.h>

#include <iostream>
#include <SDL.h>
#include <SDL_image.h>

GameObject::GameObject(const char* path) {
	IMG_LOAD img_loader(path);
	sprite.reset(createSprite(img_loader.image));
}

GameObject::GameObject(SDL_Surface* image) {
	sprite.reset(createSprite(image));
}

GameObject::GameObject(GameObject&& game_object) {
	sprite = std::move(game_object.sprite);
	game_object.sprite = nullptr;

	window_w = game_object.window_w;
	window_h = game_object.window_h;

	speed = game_object.speed;

	x = game_object.x;
	y = game_object.y;
}

GameObject& GameObject::operator=(GameObject&& game_object) {
	sprite = std::move(game_object.sprite);
	game_object.sprite = nullptr;

	window_w = game_object.window_w;
	window_h = game_object.window_h;

	speed = game_object.speed;

	x = game_object.x;
	y = game_object.y;

	return *this;
}


void GameObject::Render() const {
	sprite->Render();
}