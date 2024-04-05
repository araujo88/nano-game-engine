#include "../include/NPC.hpp"

using namespace nano;

NPC::NPC(std::string name, int x, int y, SDL_Renderer *renderer,
         std::string spritePath)
    : Character(name, x, y, renderer, spritePath) {
  std::mt19937 gen(rd()); // Standard mersenne_twister_engine seeded with rd()

  std::uniform_int_distribution<> distribX(0, WINDOW_WIDTH);
  std::uniform_int_distribution<> distribY(0, WINDOW_HEIGHT);

  this->x = distribX(gen);
  this->y = distribY(gen);
};

void NPC::move() {
  std::mt19937 gen(rd()); // Standard mersenne_twister_engine seeded with rd()

  std::uniform_int_distribution<> distribX(-max_speed, max_speed);
  std::uniform_int_distribution<> distribY(-max_speed, max_speed);

  int speed_x = distribX(gen);
  int speed_y = distribY(gen);

  // Calculate potential new positions
  int new_x = x + speed_x;
  int new_y = y + speed_y;

  // Ensure the NPC doesn't move off the left or right side of the screen
  if (new_x < 0) {
    x = 0; // Prevent moving off the left edge
  } else if (new_x > WINDOW_WIDTH - TILE_SIZE) { // Adjust for the NPC's size
    x = WINDOW_WIDTH - TILE_SIZE; // Prevent moving off the right edge
  } else {
    x = new_x; // Update x if within bounds
  }

  // Ensure the NPC doesn't move off the top or bottom of the screen
  if (new_y < 0) {
    y = 0; // Prevent moving off the top edge
  } else if (new_y > WINDOW_HEIGHT - TILE_SIZE) { // Adjust for the NPC's size
    y = WINDOW_HEIGHT - TILE_SIZE; // Prevent moving off the bottom edge
  } else {
    y = new_y; // Update y if within bounds
  }

  // Update the bounding box position
  this->boundingBox.x = x;
  this->boundingBox.y = y;
}

void NPC::update() {
  Uint32 currentTime = SDL_GetTicks(); // Get the current number of milliseconds
                                       // since SDL was initialized
  if (currentTime - lastMoveTime > 100) {
    move();
    lastMoveTime = currentTime; // Update the last move time
  }
}

void NPC::render(SDL_Renderer *renderer) { Character::render(renderer); }

bool NPC::isColliding(const SDL_Rect &box) {
  return Character::isColliding(box);
}

std::string NPC::getName() { return Character::getName(); };

SDL_Rect NPC::getBoundingBox() { return Character::getBoundingBox(); };

void NPC::handleCollision(IEntity *entity) {}

void NPC::handleEvent(SDL_Event *event) {}
