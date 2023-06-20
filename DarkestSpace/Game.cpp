#include "Game.hpp"
#include "TextureManager.hpp"
#include "Map.hpp"
#include "Components.hpp"
#include "Vector2D.hpp"
#include "Collision.hpp"
#include "AssetManager.hpp"

SDL_Texture* playerTex;

//something missing here
Map* map;
Manager manager;

SDL_Renderer* Game::renderer = nullptr;
SDL_Event Game::event;

AssetManager* Game::assets = new AssetManager(&manager);

std::vector<ColliderComponent*> Game::colliders;

auto& player(manager.addEntity());
auto& wall(manager.addEntity());

enum groupLabels : std::size_t
{
	groupMap,
	groupPlayers,
	groupEnemies,
	groupColliders
};

auto& tiles(manager.getGroup(groupMap));
auto& players(manager.getGroup(groupPlayers));
auto& enemies(manager.getGroup(groupEnemies));

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

	player.addComponent<PositionComponent>(2);
	player.addComponent<SpriteComponent>("assets/player_idle.png", true);
	//commenting out old sprite component for testing animated one
	//player.addComponent<SpriteComponent>("assets/playerIcon.png");
	player.addComponent<KeyboardController>();
	player.addComponent<ColliderComponent>("player");
	player.addGroup(groupPlayers);

	wall.addComponent<PositionComponent>(300.0f, 300.0f, 300, 20, 1);
	wall.addComponent<SpriteComponent>("wall.png");
	wall.addComponent<ColliderComponent>("wall");
	wall.addGroup(groupMap);

	assets->AddTexture("terrain", "assets/terrain_ss.png");
	assets->AddTexture("player", "resource Files/player_anims.png");
	assets->AddTexture("projectile", "assets/projectile.png");//temp, need to make said file

	assets->CreateProjectile(Vector2D(600, 600), Vector2D(2, 0), 200, 2, "projectile");
	assets->CreateProjectile(Vector2D(500, 550), Vector2D(1, 0), 200, 2, "projectile");
	assets->CreateProjectile(Vector2D(400, 400), Vector2D(3, 0), 200, 2, "projectile");
	assets->CreateProjectile(Vector2D(300, 300), Vector2D(1, 0), 200, 2, "projectile");
	assets->CreateProjectile(Vector2D(200, 200), Vector2D(1, -1), 200, 2, "projectile");

	map = new Map();	// TODO: improve mappage

	Map::LoadMap("assets/p16x16test1.map", 16, 16);

	SDL_Surface* tmpSurface = IMG_Load("assets/player.png");

};

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
	}

	for (auto& p : projectiles)
	{
		if (Collision::AABB(player.getComponent<ColliderComponent>().collider, p->getComponent<ColliderComponent>().collider))
		{
			std::cout << "Hit player" << std::endl;
			p->destroy();
		}
	}
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
	for (auto& e : enemies)
	{
		e->draw();
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

void Game::AddTile(int id, int x, int y) {
	auto& tile(manager.addEntity());
	tile.addComponent<TileComponent>(x, y, 32, 32, id);
	tile.addGroup(groupMap);
}