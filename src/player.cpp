#include "../include/player.hpp"

using namespace nano;

Player::Player(int x, int y, int speed, SDL_Renderer *renderer,
               std::string spritePath)
    : x(x), y(y), speed(speed) {
  texture = IMG_LoadTexture(renderer, spritePath.c_str());
  if (!texture) {
    SDL_Log("Failed to load player texture: %s", IMG_GetError());
    exit(1);
  }
};

void Player::moveUp() {
  SDL_LogDebug(SDL_LOG_CATEGORY_APPLICATION, "Moving up");
  if (y > 0) {
    y -= speed;
  }
}

void Player::moveDown() {
  SDL_LogDebug(SDL_LOG_CATEGORY_APPLICATION, "Moving down");
  if (y < WINDOW_HEIGHT - TILE_SIZE) {
    y += speed;
  }
}

void Player::moveLeft() {
  SDL_LogDebug(SDL_LOG_CATEGORY_APPLICATION, "Moving left");
  if (x > 0) {
    x -= speed;
  }
}

void Player::moveRight() {
  SDL_LogDebug(SDL_LOG_CATEGORY_APPLICATION, "Moving right");
  if (x < WINDOW_WIDTH - TILE_SIZE) {
    x += speed;
  }
}

void Player::render(SDL_Renderer *renderer) {
  SDL_Rect playerRect = {x, y, TILE_SIZE, TILE_SIZE};
  SDL_RenderCopy(renderer, texture, NULL, &playerRect);
}

void Player::handleEvent(SDL_Event *event) {
  if (event->type == SDL_KEYDOWN) {
    SDL_LogDebug(SDL_LOG_CATEGORY_APPLICATION, "Player position: %d(x) %d(y)",
                 this->x, this->y);

    switch (event->key.keysym.sym) {
    case SDLK_UP:
      moveUp();
      break;
    case SDLK_DOWN:
      moveDown();
      break;
    case SDLK_LEFT:
      moveLeft();
      break;
    case SDLK_RIGHT:
      moveRight();
      break;
    }
  }
}

Player::~Player() { SDL_DestroyTexture(texture); }
