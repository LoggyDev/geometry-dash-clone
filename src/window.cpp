#include "window.hpp"
SDL_Renderer* window::ren = nullptr;
SDL_Window* window::win = nullptr;

window::window() {    
    win = SDL_CreateWindow("denial [ld]", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 1152, 864, 0);
    ren = SDL_CreateRenderer(win, -1, SDL_RENDERER_PRESENTVSYNC);
}

window::~window() {
    SDL_DestroyWindow(window::win);
    SDL_DestroyRenderer(window::ren);
}

void window::wn_render() {
	SDL_RenderPresent(window::ren);
}

void window::wn_clear() {
	SDL_RenderClear(window::ren);
}