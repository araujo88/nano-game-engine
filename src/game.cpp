#include "../include/game.hpp"

using namespace nano;

Game::Game(std::string title) {
  title = title;

  SDL_LogSetAllPriority(SDL_LOG_PRIORITY_VERBOSE);

  if (SDL_Init(SDL_INIT_VIDEO) != 0) {
    SDL_Log("Unable to initialize SDL: %s", SDL_GetError());
    exit(1);
  }

  window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_UNDEFINED,
                            SDL_WINDOWPOS_UNDEFINED, WINDOW_WIDTH,
                            WINDOW_HEIGHT, SDL_WINDOW_SHOWN);

  if (!window) {
    SDL_Log("Unable to create window: %s", SDL_GetError());
    exit(1);
  }

  renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_SOFTWARE);
  if (!renderer) {
    SDL_Log("Unable to create renderer: %s", SDL_GetError());
    exit(1);
  }

  if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG)) {
    SDL_Log("Unable to initialize SDL_image: %s", IMG_GetError());
    exit(1);
  }
}

SDL_Renderer *Game::getRenderer() { return renderer; }

void Game::clear() {
  SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
  SDL_RenderClear(renderer);
}

void Game::update() {
  SDL_RenderPresent(renderer);

  // Update all entities
  for (auto &entity : entities) {
    entity->update();
  }

  // Check for collisions between all entities
  for (auto &entity1 : entities) {
    for (auto &entity2 : entities) {
      // Avoid self-collision and redundant checks
      if (entity1 != entity2 &&
          entity1->isColliding(entity2->getBoundingBox())) {
        entity1->handleCollision(entity2);
        entity2->handleCollision(entity1);
      }
    }
  }

  // Remove all entities marked for destruction
  entities.erase(
      std::remove_if(entities.begin(), entities.end(),
                     [](IEntity *entity) { return entity->shouldDestroy(); }),
      entities.end());
}

void Game::handleEvents() {
  while (SDL_PollEvent(&event)) {
    if (event.type == SDL_QUIT) {
      isRunning = false;
    }
    for (auto &entity : entities) {
      entity->handleEvent(&event);
    }
  }
}

void Game::addEntity(IEntity *entity) { this->entities.push_back(entity); }

void Game::renderEntities() {
  for (auto &entity : this->entities) {
    entity->render(renderer);
  }
}

void Game::mainLoop() {
  while (isRunning) {
    handleEvents();
    clear();
    renderEntities();
    update();
  }
}

Game::~Game() {
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  SDL_Quit();
}
