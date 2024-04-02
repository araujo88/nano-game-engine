#ifndef WORLD_H_
#define WORLD_H_

#include "constants.hpp"
#include "entity.hpp"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

namespace nano {
class World : public IEntity {
private:
  enum TileType {
    TILE_GRASS = 0,
    TILE_WATER,
    TILE_ROAD,
  };
  int tiles[WORLD_WIDTH][WORLD_HEIGHT];
  SDL_Texture *grassTexture; // As an example

public:
  World(SDL_Renderer *renderer, std::string spritePath);
  void render(SDL_Renderer *renderer) override;
  void handleEvent(SDL_Event *event) override;
  void update() override;
  ~World();
};
} // namespace nano

#endif