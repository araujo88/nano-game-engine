#include "../include/NPC.hpp"

using namespace nano;

NPC::NPC(SDL_Renderer *renderer, std::string spritePath) {
  std::mt19937 gen(rd()); // Standard mersenne_twister_engine seeded with rd()

  std::uniform_int_distribution<> distribX(0, WINDOW_WIDTH);
  std::uniform_int_distribution<> distribY(0, WINDOW_HEIGHT);

  this->x = distribX(gen);
  this->y = distribY(gen);

  texture = IMG_LoadTexture(renderer, spritePath.c_str());
  if (!texture) {
    SDL_Log("Failed to load NPC texture: %s", IMG_GetError());
    exit(1);
  }
};

void NPC::move() {
  std::mt19937 gen(rd()); // Standard mersenne_twister_engine seeded with rd()

  std::uniform_int_distribution<> distribX(-max_speed, max_speed);
  std::uniform_int_distribution<> distribY(-max_speed, max_speed);

  int speed_x = distribX(gen);
  int speed_y = distribY(gen);

  if ((x < WINDOW_WIDTH - TILE_SIZE) && (x > 0)) {
    x += speed_x;
  }
  if ((y < WINDOW_HEIGHT - TILE_SIZE) && (y > 0)) {
    y += speed_y;
  }
}

void NPC::render(SDL_Renderer *renderer) {
  SDL_Rect NPCRect = {x, y, TILE_SIZE, TILE_SIZE};
  SDL_RenderCopy(renderer, texture, NULL, &NPCRect);
}

void NPC::update() {
  Uint32 currentTime = SDL_GetTicks(); // Get the current number of milliseconds
                                       // since SDL was initialized
  if (currentTime - lastMoveTime > 100) {
    move();
    lastMoveTime = currentTime; // Update the last move time
  }
}

void NPC::handleEvent(SDL_Event *event) {}

NPC::~NPC() { SDL_DestroyTexture(texture); }
