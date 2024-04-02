#include "../include/world.hpp"

using namespace nano;

World::World(SDL_Renderer *renderer, std::string spritePath) {
  this->name = "World";
  // Initialize the world tiles (for now, let's say everything is grass)
  for (int i = 0; i < WORLD_WIDTH; i++) {
    for (int j = 0; j < WORLD_HEIGHT; j++) {
      tiles[i][j] = TILE_GRASS;
    }
  }

  // Load grass texture
  grassTexture = IMG_LoadTexture(renderer, spritePath.c_str());
  if (!grassTexture) {
    SDL_Log("Failed to load grass texture: %s", IMG_GetError());
    exit(1);
  }
}

void World::render(SDL_Renderer *renderer) {
  for (int i = 0; i < TILES_X; ++i) {
    for (int j = 0; j < TILES_Y; ++j) {
      SDL_Rect dest = {i * TILE_SIZE, j * TILE_SIZE, TILE_SIZE, TILE_SIZE};

      // Render based on the tile type
      switch (tiles[i][j]) {
      case TILE_GRASS:
        SDL_RenderCopy(renderer, grassTexture, NULL, &dest);
        break;
        // ... other tiles
      }
    }
  }
}

void World::handleEvent(SDL_Event *event) {
  // Handle any world-specific events (for now, do nothing)
}

void World::update() {}

bool World::isColliding(const SDL_Rect &box) { return false; }

std::string World::getName() { return this->name; };

SDL_Rect World::getBoundingBox() { return this->boundingBox; };

void World::handleCollision() {}

World::~World() {
  SDL_DestroyTexture(grassTexture);
  // Destroy other textures if added
}