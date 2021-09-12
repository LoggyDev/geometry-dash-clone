#include "sprite.hpp"
#include "player.hpp"
#include <vector>
#include <fstream>

class scene {
public:
	scene(SDL_Renderer* ren);
	void update(SDL_Renderer* ren, int input);
	bool triggerActivated(int x);

	sprite line;
	sprite tile;
	sprite floor;
	sprite background;
	player cube;

	int shiftVal         = 1;
	int p_red            = 62;
	int p_green          = 49;
	int p_blue           = 255;
	int c_red            = 62;
	int c_green          = 49;
	int c_blue           = 255;
	bool editing         = 1;
	int backgroundScroll = 0;
	int floorScroll      = 0;
	int scrollFactor     = 8;
	float acc            = 0;
	int tim              = 0;
	int level_x          = 1000;
	int level_y          = 4;
	float scale          = 1;
	float scaleSize      = 1;
	int lower            = 0;
	int color            = 0;
	int IdealColor       = 0;	
};