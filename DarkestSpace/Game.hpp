#ifndef Game_hpp
#define Game_hpp

#include <SDL.h>
#include <iostream>

class Game
{
public:
	Game();
	~Game();

	void init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen);

	void handleEvents();
	void update();
	void render();
	void clean();

	bool running() { return isRunning; }

	static SDL_Renderer* renderer;
	static SDL_Event event;

private:
	bool isRunning;
	int cnt = 0;
	SDL_Window* window;
};



#endif // !Game_hpp
