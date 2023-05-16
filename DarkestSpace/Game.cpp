#include "Game.hpp"
#include "TextureManager.hpp"
#include "GameObject.hpp"
#include "Map.hpp"

#include "ECS.hpp"
#include "Components.hpp"

GameObject* player;
GameObject* enemy;
//something missing here
Map* map;

SDL_Renderer* Game::renderer = nullptr;

Manager manager;
auto& newPlayer(manager.addEntity());


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

	// Removes 3 lines of code (see ep. #2)
	// Followed by adding a line to show playerTex

	player = new GameObject("assets/player.png", 0, 0);

	enemy = new GameObject("assets/enemy.png", 50, 50);

	map = new Map();

	// Technically neither playerTex nor player.png exist yet.

	newPlayer.addComponent<PositionComponent>();
	newPlayer.getComponent<PositionComponent>().setPos(500, 500);

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

	player->Update();
	enemy->Update();

	manager.update();
	std::cout << newPlayer.getComponent<PositionComponent>().x() << "," <<
		newPlayer.getComponent<PositionComponent>().y() << std::endl;

}

void Game::render() {
	SDL_RenderClear(renderer);
	map->DrawMap();
	//Rendering stuff goes here
	player->Render();
	enemy->Render();
	SDL_RenderPresent(renderer);
}

void Game::clean() {
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_QUIT();
	std::cout << "Cleaned up. Exiting." << std::endl;
}