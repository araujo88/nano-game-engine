#include "../include/player.hpp"

using namespace nano;

Player::Player(std::string name, SDL_Renderer *renderer, std::string spritePath)
    : Character(name, x, y, renderer, spritePath) {
  this->x = 0;
  this->y = 0;
  this->speed = 10;
  this->renderer = renderer;
};

Player::Player(std::string name, int x, int y, int speed,
               SDL_Renderer *renderer, std::string spritePath)
    : Character(name, x, y, renderer, spritePath) {
  this->x = x;
  this->y = y;
  this->speed = speed;
  this->renderer = renderer;
};

void Player::moveUp() {
  // SDL_LogDebug(SDL_LOG_CATEGORY_APPLICATION, "Moving up");
  if (y > 0) {
    y -= speed;
  }
  this->boundingBox.y = y;

  isFacingUp = true;
  isFacingDown = false;
  isFacingRight = false;
  isFacingLeft = false;
}

void Player::moveDown() {
  // SDL_LogDebug(SDL_LOG_CATEGORY_APPLICATION, "Moving down");
  if (y < WINDOW_HEIGHT - TILE_SIZE) {
    y += speed;
  }
  this->boundingBox.y = y;

  isFacingUp = false;
  isFacingDown = true;
  isFacingRight = false;
  isFacingLeft = false;
}

void Player::moveLeft() {
  // SDL_LogDebug(SDL_LOG_CATEGORY_APPLICATION, "Moving left");
  if (x > 0) {
    x -= speed;
  }
  this->boundingBox.x = x;

  isFacingUp = false;
  isFacingDown = false;
  isFacingRight = false;
  isFacingLeft = true;
}

void Player::moveRight() {
  // SDL_LogDebug(SDL_LOG_CATEGORY_APPLICATION, "Moving right");
  if (x < WINDOW_WIDTH - TILE_SIZE) {
    x += speed;
  }
  this->boundingBox.x = x;

  isFacingUp = false;
  isFacingDown = false;
  isFacingRight = true;
  isFacingLeft = false;
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
    case SDLK_RETURN:
      attack();
      SDL_LogDebug(SDL_LOG_CATEGORY_APPLICATION, "enter pressed!!!!");
    }
  }
}

void Player::attack() {
  if (isFacingDown) {
    auto bullet = std::make_unique<Projectile>(
        "Bullet", x, y, renderer, "sprites/pepe.png", Direction::DOWN);
    bullets.push_back(std::move(bullet));
  }
  if (isFacingUp) {
    auto bullet = std::make_unique<Projectile>(
        "Bullet", x, y, renderer, "sprites/pepe.png", Direction::UP);
    bullets.push_back(std::move(bullet));
  }
  if (isFacingRight) {
    auto bullet = std::make_unique<Projectile>(
        "Bullet", x, y, renderer, "sprites/pepe.png", Direction::RIGHT);
    bullets.push_back(std::move(bullet));
  }
  if (isFacingLeft) {
    auto bullet = std::make_unique<Projectile>(
        "Bullet", x, y, renderer, "sprites/pepe.png", Direction::LEFT);
    bullets.push_back(std::move(bullet));
  }
}

void Player::render(SDL_Renderer *renderer) {
  Character::render(renderer);
  for (auto &bullet : bullets) {
    bullet->render(renderer);
  }
}

bool Player::isColliding(const SDL_Rect &box) {
  return Character::isColliding(box);
}

std::string Player::getName() { return Character::getName(); };

SDL_Rect Player::getBoundingBox() { return Character::getBoundingBox(); };

void Player::handleCollision(IEntity *entity) {
  for (auto &bullet : bullets) {
    bullet->handleCollision(entity);
  }
}

void Player::update() {
  for (auto &bullet : bullets) {
    bullet->update();
  }

  // Remove bullets that are out of bounds or have collided with something
  bullets.erase(std::remove_if(bullets.begin(), bullets.end(),
                               [](const std::unique_ptr<Projectile> &bullet) {
                                 return bullet->isOutOfBounds();
                               }),
                bullets.end());
}
