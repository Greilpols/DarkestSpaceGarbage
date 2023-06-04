#include "Game.hpp"
#include "TextureManager.hpp"
#include "Map.hpp"
#include "Components.hpp"
#include "Vector2D.hpp"
#include "Collision.hpp"

//something missing here
Map* map;
Manager manager;

SDL_Renderer* Game::renderer = nullptr;
SDL_Event Game::event;

std::vector<ColliderComponent*> Game::colliders;

auto& player(manager.addEntity());
auto& wall(manager.addEntity());

// test a few tiles for collisioning
auto& tile0(manager.addEntity());
auto& tile1(manager.addEntity());
auto& tile2(manager.addEntity());

Game::Game()
{}
Game::~Game()
{}



void Game::init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen)
{
	int flags = 0;
	if (fullscreen) {
		flags = SDL_WINDOW_FULLSCREEN;
	}

	if (SDL_init(SDL_INIT_EVERYTHING) == 0)
	{
		std::cout << "Subsystems initialized(SDL init)" << std::endl;

		window = SDL_CreateWindow(title, xpos, ypos, width, height, flags);
		if (window) {
			std::cout << "Window be up" << std::endl;
		}

		renderer = SDL_CreateRenderer(window, -1, 0);
		if (renderer) {
			SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
			std::cout << "Renderer be up" << std::endl;
		}

		isRunning = true;
	}
	else {
		isRunning = false;
	}

	tile0.addComponent<TileComponent>(220, 220, 32, 32, 0);
	tile1.addComponent<TileComponent>(130, 150, 32, 32, 1);
	tile1.addComponent<ColliderComponent>("dirt");
	tile2.addComponent<TileComponent>(75, 75, 32, 32, 2);
	tile2.addComponent<ColliderComponent>("grass");

	player.addComponent<PositionComponent>(2);
	player.addComponent<SpriteComponent>("assets/playerIcon.png");
	player.addComponent<KeyboardController>();
	player.addComponent<ColliderComponent>("player");

	wall.addComponent<PositionComponent>(300.0f, 300.0f, 300, 20, 1);
	wall.addComponent<SpriteComponent>("testTexture.png");
	wall.addComponent<ColliderComponent>("wall");

	map = new Map();

	// Technically neither playerTex nor player.png exist yet.

}

void Game::handleEvents()
{
	SDL_Event event;



	SDL_PollEvent(&event);
	switch (event.type) {
	case SDL_QUIT:
		isRunning = false;
		break;

	default:
		break;
	}
}

void Game::update() {

	manager.refresh();
	manager.update();

	if (Collision::AABB(player.getComponent<ColliderComponent>().collider,
		wall.getComponent<ColliderComponent>().collider))
	{
		player.getComponent<PositionComponent>().velocity * -1; // swaps direction (minor bounce to make player stop at wall)
		// if just stopping speed, it'd cause the player to get +1 deeper into the wall by just holding button down
		std::cout << "Hit a wall" << std::endl;	//just for testing for now, make sure collision properly functions
	}
}

void Game::render() {
	SDL_RenderClear(renderer);
	map->DrawMap();
	//Rendering stuff goes here
	manager.draw();
	SDL_RenderPresent(renderer);
}

void Game::clean() {
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_QUIT();
	std::cout << "Cleaned up. Exiting." << std::endl;
}