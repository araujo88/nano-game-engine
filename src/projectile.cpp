#include "../include/projectile.hpp"

using namespace nano;

Projectile::Projectile(std::string name, int x, int y, SDL_Renderer *renderer,
                       std::string spritePath, Direction direction)
    : Character(name, x, y, renderer, spritePath) {
  SDL_LogDebug(SDL_LOG_CATEGORY_APPLICATION, "Bullet created!!!!");

  this->name = name;
  this->x = x;
  this->y = y;
  this->direction = direction;
};

void Projectile::move() {
  switch (this->direction) {
  case Direction::UP:
    y -= speed;
    break;
  case Direction::DOWN:
    y += speed;
    break;
  case Direction::LEFT:
    x -= speed;
    break;
  case Direction::RIGHT:
    x += speed;
    break;
  }

  // Update the bounding box position
  this->boundingBox.x = x;
  this->boundingBox.y = y;
}

void Projectile::update() {
  Uint32 currentTime = SDL_GetTicks(); // Get the current number of milliseconds
                                       // since SDL was initialized
  if (currentTime - lastMoveTime > 100) {
    move();
    lastMoveTime = currentTime; // Update the last move time
  }
}

void Projectile::render(SDL_Renderer *renderer) { Character::render(renderer); }

bool Projectile::isColliding(const SDL_Rect &box) {
  return Character::isColliding(box);
}

std::string Projectile::getName() { return Character::getName(); };

SDL_Rect Projectile::getBoundingBox() { return Character::getBoundingBox(); };

void Projectile::handleCollision(IEntity *entity) {
  if (entity->getName() == "NPC") {
    SDL_LogDebug(SDL_LOG_CATEGORY_APPLICATION, "HITTED A CHUD!!");
    entity->markForDestruction(); // Mark the NPC for destruction
  }
}

bool Projectile::isOutOfBounds() {
  if (x < 0)
    return true;
  if (y < 0)
    return true;
  if (x > WINDOW_WIDTH)
    return true;
  if (y > WINDOW_HEIGHT)
    return true;
  return false;
}

void Projectile::handleEvent(SDL_Event *event) {}

Projectile::~Projectile() {
  SDL_LogDebug(SDL_LOG_CATEGORY_APPLICATION, "Bullet destroyed!!!!");
  Character::~Character();
}