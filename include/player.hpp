#include "sprite.hpp"

class player {
public: 
	player(SDL_Renderer* ren);
	player();
	void update(SDL_Renderer* ren, int input);
	void collisions(SDL_Rect tilerect);

	sprite icon;
	float rotation       = 0;
	float idealRotation  = 0;
	float acc            = 0;
};