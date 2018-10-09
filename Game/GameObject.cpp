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

void GameObject::Render() const {
	sprite->Render();
}