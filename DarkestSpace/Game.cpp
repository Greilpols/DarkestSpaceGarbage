#include "Game.hpp"
#include "TextureManager.hpp"
#include "Map.hpp"
#include "Components.hpp"
#include "Vector2D.hpp"
#include "Collision.hpp"
#include "AssetManager.hpp"

Map* map;
Manager manager;

SDL_Renderer* Game::renderer = nullptr;
SDL_Event Game::event;

AssetManager* Game::assets = new AssetManager(&manager);

SDL_Rect Game::camera = { 0, 0, 800, 640 };
bool Game::isRunning = false;

auto& player(manager.addEntity());

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

	if (SDL_Init(SDL_INIT_EVERYTHING) == 0)
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

	player.addComponent<PositionComponent>(200.0f, 300.0f, 32, 32, 4);
	player.addComponent<SpriteComponent>("assets/player_idle.png", true);
	player.addComponent<KeyboardController>();
	player.addComponent<ColliderComponent>("player");
	player.addGroup(groupPlayers);

	/*wall.addComponent<PositionComponent>(300.0f, 300.0f, 300, 20, 1);
	wall.addComponent<SpriteComponent>("assets/wall.png");
	wall.addComponent<ColliderComponent>("wall");
	wall.addGroup(groupMap);*/

	assets->CreateProjectile(Vector2D(600, 600), Vector2D(2, 0), 200, 2, "projectile");
	assets->CreateProjectile(Vector2D(500, 550), Vector2D(1, 0), 200, 2, "projectile");
	assets->CreateProjectile(Vector2D(400, 400), Vector2D(3, 0), 200, 2, "projectile");
	assets->CreateProjectile(Vector2D(300, 300), Vector2D(1, 0), 200, 2, "projectile");
	assets->CreateProjectile(Vector2D(200, 200), Vector2D(1, -1), 200, 2, "projectile");

	assets->AddTexture("terrain", "assets/terrain_tiles.png");
	assets->AddTexture("player", "assets/player_anims.png");

	map = new Map("assets/terrain_tiles.png", 3, 32);

	map->LoadMap("assets/p16x16test1.map", 16, 16);

	SDL_Surface* tmpSurface = IMG_Load("assets/player.png");

};

auto& tiles(manager.getGroup(Game::groupMap));
auto& players(manager.getGroup(Game::groupPlayers));
auto& projectiles(manager.getGroup(Game::groupProjectiles));


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

	Vector2D pVel = player.getComponent<PositionComponent>().velocity;
	int pSpeed = player.getComponent<PositionComponent>().speed;

	for (auto t : tiles)
	{
		t->getComponent<TileComponent>().destRect.x += -(pVel.x * pSpeed);
		t->getComponent<TileComponent>().destRect.y += -(pVel.y * pSpeed);
	}

	for (auto& p : projectiles)
	{
		if (Collision::AABB(player.getComponent<ColliderComponent>().collider, p->getComponent<ColliderComponent>().collider))
		{
			std::cout << "Hit player" << std::endl;
			p->destroy();
		}
	}
	camera.x = player.getComponent<PositionComponent>().position.x - 400;
	camera.y = player.getComponent<PositionComponent>().position.y - 320;

	if (camera.x < 0)
		camera.x = 0;
	if (camera.y < 0)
		camera.y = 0;
	if (camera.x > camera.w)
		camera.x = camera.w;
	if (camera.x > camera.h)
		camera.x = camera.h;
}

void Game::render() {
	SDL_RenderClear(renderer);
	for (auto& t : tiles)
	{
		t->draw();
	}
	for (auto& p : players)
	{
		p->draw();
	}
	for (auto& p : projectiles)
	{
		p->draw();
	}

	SDL_RenderPresent(renderer);
}

void Game::clean() {
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
	std::cout << "Cleaned up. Exiting." << std::endl;
}

