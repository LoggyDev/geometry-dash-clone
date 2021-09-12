#pragma once

struct worldTile {
	int x        = 0;
	int y        = 0; 
	int w        = 0; 
	int h        = 0;
	int xx       = 0;
	int yy       = 0; 
	int offset_y = 0;
	int id       = 0;
	int rot      = 0; 
	int opp      = 0; 
	int type     = 0;
	int x_1      = 0;
	int y_1      = 0;

	worldTile(int x_, int y_, int w_, int h_, int xx_, int yy_, int rot_, int id_) {
		x = x_;
		y = y_;
		w = w_;
		h = h_;
		xx = xx_;
		yy = yy_;
		offset_y = w_;
		rot = rot_;
		id = id_;
	}
};
