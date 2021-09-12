#include "sprite.hpp"
sprite::sprite() {}
sprite::sprite(const char* path, int x, int y, int w, int h, SDL_Renderer* renderer) {
	desrect = { x, y, w, h };
	srcrect = { 0, 0, w, h };
	image = SDL_LoadBMP(path);
	texture = SDL_CreateTextureFromSurface(renderer, image);
}

void sprite::setColor(int r, int g, int b) {
	SDL_SetTextureColorMod(texture, r, g, b);
}

sprite::~sprite() {}

void sprite::draw(SDL_Renderer* renderer) {
	SDL_RenderCopy(renderer, texture, &srcrect, &desrect);
}

void sprite::draw(SDL_Renderer* renderer, int rotation) {
    SDL_RenderCopyEx(renderer, texture, &srcrect, &desrect, rotation, NULL, SDL_FLIP_NONE);
}

void sprite::setPosition(int x, int y) {
	desrect = { x, y, desrect.w, desrect.h };
}
