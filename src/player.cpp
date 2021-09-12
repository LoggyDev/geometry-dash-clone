#include "player.hpp"
#include <tgmath.h>
#include <iostream>
float lerp (float a, float b, float f) {
    return (a * (1.0f - f)) + (b * f);
}

player::player(SDL_Renderer* ren) {
	icon = sprite("res/player.bmp", 360, 0/*645 - 64*/, 64, 64, ren);
	icon.srcrect = { 0, 0, 121, 121 };
}
player::player() {}

void player::collisions(SDL_Rect tilerect) {
	/* handle collisions */
	if((icon.desrect.y >= tilerect.y-(128 / 2)) && (icon.desrect.y <= tilerect.y) &&  (icon.desrect.x >= tilerect.x-128 / 2) && (icon.desrect.x < tilerect.x + (128 / 2))) {
		icon.desrect.y = tilerect.y-(128 / 2);
		acc = 0;
	}
}

void player::update(SDL_Renderer* ren, int input) {
	if(icon.desrect.y >= 582) { icon.desrect.y = 582; acc = 0; }
	if((input) && (acc == 0)) {
		acc = -23;
	}
	if(acc == 0) 
		rotation = lerp(rotation, idealRotation, 0.4f);
	if(acc != 0) {
		rotation += 3.5;
		idealRotation = round(rotation/90)*90;
	}
	if(rotation > 360) rotation = 0;
	acc += 1.8;
	if(acc >= 23) acc = 23;
	icon.desrect.y += acc;
	icon.draw(ren, round(rotation));
}