#include "scene.hpp"
#include "utility.hpp"
#include "iostream"

std::ifstream levelData("res/test.bin");
std::vector<dataToken> currTile;

double approach(double a, double b, double c) {
	if (a < b) return std::min(a + c, b); else return std::max(a - c, b);
}

bool scene::triggerActivated(int x) {
	if(x == cube.icon.desrect.x) { return 1; } else return 0;
}

scene::scene(SDL_Renderer* ren) {
	/* play background music */
	SDL_Init(SDL_INIT_AUDIO);
	SDL_LoadWAV("res/audio/reminiscence.wav", &wavSpec, &wavBuffer, &wavLength);
	SDL_AudioDeviceID deviceId = SDL_OpenAudioDevice(NULL, 0, &wavSpec, NULL, 0);
	SDL_QueueAudio(deviceId, wavBuffer, wavLength);
	SDL_PauseAudioDevice(deviceId, 0);

	/* loading sprites */
	background = sprite("res/background/game_bg_01_001-hd.bmp",0,0,1024,1024, ren);
	floor =      sprite("res/ground/groundSquare_01_001-hd.bmp",0,645,256,256, ren);
	line =       sprite("res/line.bmp", 0, 644, 1152, 3, ren);
	tile =       sprite("res/tiles/GJ_GameSheet.bmp", 0, 0, 64, 64, ren);
	cube =       player(ren);
	tile.srcrect = { 0, 0, 32, 32 };

	int a, b, c, d, e, f, g, h;
	while(levelData>>a>>b>>c>>d>>e>>f>>g>>h) {
		currTile.emplace_back(a,b,c,d,e,f,g,h);
	}
}

scene::~scene() {
	SDL_CloseAudioDevice(deviceId);
	SDL_FreeWAV(wavBuffer);
}

void scene::update(SDL_Renderer* ren, int input) {
	backgroundScroll -= scrollFactor / 6;
	level_x -= scrollFactor;

	/* drawing the background */
	for(int i = 0; i < 3; ++i) {
		background.setPosition(i * 1024 + backgroundScroll, 0);
		background.draw(ren);
	} if(backgroundScroll < -1024) backgroundScroll = 0;
	
	/* color system */
	c_red =   approach(c_red, p_red, shiftVal);
	c_green = approach(c_green, p_green, shiftVal);
	c_blue =  approach(c_blue, p_blue, shiftVal);
 	background.setColor(c_red, c_green, c_blue);
 	floor.setColor(c_red, c_green, c_blue);

	/* drawing the level */
	for(size_t i = 0; i < currTile.size(); ++i) {
		/* set tile to level data */
		tile.desrect = { (currTile[i].b * 64) + level_x, ((currTile[i].c * 64)) + level_y, currTile[i].d, currTile[i].e };
		tile.srcrect.x = currTile[i].f * 32;
		tile.srcrect.y = currTile[i].g * 32;

		/* frustum culling */
		if ((tile.desrect.x > 0) or (tile.desrect.x < 1024)) {
			if((tile.desrect.x > 128) and (tile.desrect.x < 1024 + 68))
				currTile[i].opp = approach(currTile[i].opp, 255, 10);  
			else
				currTile[i].opp = approach(currTile[i].opp, 0, 10); 
			/* tile types + trigger functions */
			switch(currTile[i].a) {
				case(0): 
					cube.collisions(tile.desrect);
				break;
				case(1): 
				if(triggerActivated(tile.desrect.x)) {
						p_red =    currTile[i].c; 
						p_green =  currTile[i].d; 
						p_blue =   currTile[i].e; 
						shiftVal = currTile[i].f; 
				} break;
				case(2): if(tile.desrect.x == 360) { 
						scrollFactor = currTile[i].c; 
				} break;
			}
			/* draw tile */
			SDL_SetTextureAlphaMod(tile.texture, currTile[i].opp);
			tile.draw(ren, currTile[i].h);
		}
	} 
	/* drawing the floor */
	floorScroll -= scrollFactor;
	if(floorScroll <= -256) floorScroll = 0;

	for(int i = 0; i < 8; ++i) {
		floor.setPosition(i*256+floorScroll, 645);
		floor.draw(ren);
	}

	scene::line.draw(ren);
	cube.update(ren, input);
}

