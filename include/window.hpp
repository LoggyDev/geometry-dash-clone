#pragma once
#include "SDL2/SDL.h"

class window {
public:
	window();
	~window();
	void wn_clear();
	void wn_render();

	static SDL_Renderer* ren;
	static SDL_Window* win;
};
