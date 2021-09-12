#include "scene.hpp"
#include "utility.hpp"
#include "iostream"
double approach(double a, double b, double c) {
	if (a < b) return std::min(a + c, b); else return std::max(a - c, b);
}

std::ifstream levelData("res/test.bin");
std::vector<worldTile> currTile;

bool scene::triggerActivated(int x) {
	if(x/scrollFactor == cube.icon.desrect.x) { return 1; } else return 0;
}

scene::scene(SDL_Renderer* ren) {
	/* loading sprites */
	background = sprite("res/background/game_bg_01_001-hd.bmp",0,0,1024,1024, ren);
	floor =      sprite("res/ground/groundSquare_01_001-hd.bmp",0,645,256,256, ren);
	line =       sprite("res/line.bmp", 0, 644, 1152, 3, ren);
	tile =       sprite("res/tiles/GJ_GameSheet.bmp", 0, 0, 64, 64, ren);
	cube =       player(ren);

	/* loading sprite colors */
	background.setColor(c_red, c_green, c_blue); // default background blue ...
	floor.setColor(50, 49, 255);      			 // default floor blue ...

	/* set sprite scale on tiles */
	tile.srcrect = { 0, 0, 32, 32 };

	/* load level data */
	int x, y, w, h, xx, yy, rotation, id;
	while(levelData >> x >> y >> w >> h >> xx >> yy >> rotation >> id) {
		currTile.emplace_back(x,y,w,h,xx,yy,rotation,id);
	}
}

void scene::update(SDL_Renderer* ren, int input) {
	/* scroll the background and floor + level speed */
	backgroundScroll -= scrollFactor / 6;
	level_x -= scrollFactor;

	/* drawing the background */
	for(int i = 0; i < 3; ++i) {
		background.setPosition(i * 1024 + backgroundScroll, 0);
		background.draw(ren);
	} if(backgroundScroll < -1024) backgroundScroll = 0;
	
	/* color system */
	c_red = approach(c_red, p_red, shiftVal);
	c_green = approach(c_green, p_green, shiftVal);
	c_blue = approach(c_blue, p_blue, shiftVal);
 	background.setColor(c_red, c_green, c_blue);
 	floor.setColor(c_red, c_green, c_blue);

	/* drawing the level */
	for(size_t i = 0; i < currTile.size(); ++i) {
		/* set tile to level data */
		tile.desrect = { (currTile[i].x * 64) + level_x, ((currTile[i].y * 64)) + level_y, currTile[i].w, currTile[i].h };
		tile.srcrect.x = currTile[i].xx * 32;
		tile.srcrect.y = currTile[i].yy * 32;

		/* frustum culling */
		if ((tile.desrect.x > 0) or (tile.desrect.x < 1024)) {

			/* tile fading */
			if((tile.desrect.x > 128) and (tile.desrect.x < 1024 + 68))
				currTile[i].opp = approach(currTile[i].opp, 255, 10);  
			else
				currTile[i].opp = approach(currTile[i].opp, 0, 10); 

			/* tile types + trigger functions */
			switch(currTile[i].id) {
				/* tile collisions */
				case(0): 
					cube.collisions(tile.desrect);
				break;
				/* color trigger */
				case(1): 
					std::cout<<currTile[i].x-level_x-64<<"\n";
				if(triggerActivated(level_x-1000)) { 
						c_red = currTile[i].y; 
						c_green = currTile[i].w; 
						c_blue = currTile[i].h; 
						shiftVal = currTile[i].xx; 
					} break;
				/* speed trigger */
				case(2): if(triggerActivated(currTile[i].x)) { 
						scrollFactor = currTile[i].y; 
					} break;
			}
			/* draw tile */
			SDL_SetTextureAlphaMod(tile.texture, currTile[i].opp);
			tile.draw(ren, currTile[i].rot);
		}
	} 
	/* drawing the floor */
	floorScroll -= scrollFactor;
	if(floorScroll <= -256) floorScroll = 0;

	for(int i = 0; i < 8; ++i) {
		floor.setPosition(i*256+floorScroll, 645);
		floor.draw(ren);
	}

	/* drawing line sprite */
	scene::line.draw(ren);

	/* player events */
	cube.update(ren, input);
}

