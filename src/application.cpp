#include "application.hpp"

static window window;
int   input = 0;
scene level1(window::ren);

application::application() {
	while(running) {
		while(SDL_PollEvent(&event)) {
	    	if(event.type == SDL_QUIT) {
	     		running = false;
	    	}
		    	if(event.type == SDL_MOUSEBUTTONDOWN) {
		    		input = 1;
		    	} else {
					input = 0;	    		
		    	}
			if(event.type == SDL_KEYDOWN) {
            }
		}
		update();
		SDL_Delay(8);
	}
}

application::~application() {

}

void application::update() {
	window.wn_clear();
	level1.update(window::ren, input);
	window.wn_render();
}
