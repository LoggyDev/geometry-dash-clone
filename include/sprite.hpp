#pragma once
#include "SDL2/SDL.h"

class sprite {
public:
	sprite();
	sprite(const char* path, int x, int y, int w, int h, SDL_Renderer* renderer);
	~sprite();
	void setColor(int r, int g, int b);
	void draw(SDL_Renderer* renderer);
	void draw(SDL_Renderer* renderer, int rotation);
	void setPosition(int x, int y);
	SDL_Surface* image;
	SDL_Texture* texture;
	SDL_Rect desrect;
	SDL_Rect srcrect;
};