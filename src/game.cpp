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

  IEntity *player = nullptr;
  // Find the player entity, if it exists
  for (auto &entity : entities) {
    if (entity->getName() == "Player") {
      player = entity; // Directly use the raw pointer since entities are raw
                       // pointers
      break;           // Stop the loop once the player is found
    }
  }

  // Update all entities
  for (auto &entity : entities) {
    entity->update();
    SDL_LogDebug(SDL_LOG_CATEGORY_APPLICATION,
                 "%s bounding box: h:%d,w:%d,x:%d,y:%d",
                 entity->getName().c_str(), entity->getBoundingBox().h,
                 entity->getBoundingBox().w, entity->getBoundingBox().x,
                 entity->getBoundingBox().y);
  }

  // If a player is found, then check for collisions with other entities
  if (player) {
    for (auto &character : entities) {
      // Make sure not to check the player against itself
      if (character != player &&
          player->isColliding(character->getBoundingBox())) {
        character->handleCollision();
        SDL_LogDebug(SDL_LOG_CATEGORY_APPLICATION,
                     "Collision detected between Player and another entity.");
      }
    }
  }
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
