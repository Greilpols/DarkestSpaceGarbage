#ifndef Game_hpp
#define Game_hpp

#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include <vector>
#include "AssetManager.hpp"

class ColliderComponent;

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

	static void AddTile(int id, int x, int y);

	static SDL_Renderer* renderer;
	static SDL_Event event;
	static std::vector<ColliderComponent*> colliders;
	static AssetManager* assets;
	enum groupLabels : std::size_t
	{
		groupProjectiles
	};

private:
	bool isRunning;
	int cnt = 0;
	SDL_Window* window;
};



#endif // !Game_hpp
