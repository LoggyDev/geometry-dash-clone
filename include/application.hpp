
#include "window.hpp"
#include "sprite.hpp"
#include "scene.hpp"

class application {
public:
	application();
	~application();
	void update();
private:
	bool running = true;
	SDL_Event event;

	// put in scene
	int x = 0;
	int xx = 0;
	float acc = 0;
	float rot = 0;
	int tim = 0;
	float realrot = 0;
	int levelX = 1000;
	float scale = 1;
	float scaleSize = 1;
	int lower = 0;
	int color = 0;
	int IdealColor = 0;
};