#include "../include/player.hpp"

using namespace nano;

Player::Player(std::string name, SDL_Renderer *renderer, std::string spritePath)
    : Character(name, x, y, renderer, spritePath) {
  this->x = 0;
  this->y = 0;
  this->speed = 10;
};

Player::Player(std::string name, int x, int y, int speed,
               SDL_Renderer *renderer, std::string spritePath)
    : Character(name, x, y, renderer, spritePath) {
  this->x = x;
  this->y = y;
  this->speed = speed;
};

void Player::moveUp() {
  // SDL_LogDebug(SDL_LOG_CATEGORY_APPLICATION, "Moving up");
  if (y > 0) {
    y -= speed;
  }
  this->boundingBox.y = y;
}

void Player::moveDown() {
  // SDL_LogDebug(SDL_LOG_CATEGORY_APPLICATION, "Moving down");
  if (y < WINDOW_HEIGHT - TILE_SIZE) {
    y += speed;
  }
  this->boundingBox.y = y;
}

void Player::moveLeft() {
  // SDL_LogDebug(SDL_LOG_CATEGORY_APPLICATION, "Moving left");
  if (x > 0) {
    x -= speed;
  }
  this->boundingBox.x = x;
}

void Player::moveRight() {
  // SDL_LogDebug(SDL_LOG_CATEGORY_APPLICATION, "Moving right");
  if (x < WINDOW_WIDTH - TILE_SIZE) {
    x += speed;
  }
  this->boundingBox.x = x;
}

void Player::handleEvent(SDL_Event *event) {
  if (event->type == SDL_KEYDOWN) {
    // SDL_LogDebug(SDL_LOG_CATEGORY_APPLICATION, "Player position: %d(x)
    // %d(y)",this->x, this->y);

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

void Player::render(SDL_Renderer *renderer) { Character::render(renderer); }

bool Player::isColliding(const SDL_Rect &box) {
  return Character::isColliding(box);
}

std::string Player::getName() { return Character::getName(); };

SDL_Rect Player::getBoundingBox() { return Character::getBoundingBox(); };

void Player::handleCollision() {}

void Player::update() {}
