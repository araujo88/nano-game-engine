#include "../include/character.hpp"

using namespace nano;

Character::Character(std::string name, int x, int y, SDL_Renderer *renderer,
                     std::string spritePath) {
  texture = IMG_LoadTexture(renderer, spritePath.c_str());
  if (!texture) {
    SDL_Log("Failed to load character texture: %s", IMG_GetError());
    exit(1);
  }
  this->name = name;
  this->x = x;
  this->y = y;
  this->boundingBox = {this->x, this->y, TILE_SIZE, TILE_SIZE};

  SDL_LogDebug(SDL_LOG_CATEGORY_APPLICATION,
               "%s bounding box: h:%d,w:%d,x:%d,y:%d", this->name.c_str(),
               this->boundingBox.h, this->boundingBox.w, this->boundingBox.x,
               this->boundingBox.y);
};

void Character::render(SDL_Renderer *renderer) {
  SDL_Rect CharacterRect = {x, y, TILE_SIZE, TILE_SIZE};
  SDL_RenderCopy(renderer, texture, NULL, &CharacterRect);
}

void Character::handleEvent(SDL_Event *event) {}

void Character::update() {}

bool Character::isColliding(const SDL_Rect &box) {
  return (this->boundingBox.x < box.x + box.w) &&
         (this->boundingBox.x + this->boundingBox.w > box.x) &&
         (this->boundingBox.y < box.y + box.h) &&
         (this->boundingBox.y + this->boundingBox.h > box.y);
}

std::string Character::getName() { return this->name; };

SDL_Rect Character::getBoundingBox() { return this->boundingBox; };

void Character::handleCollision() {}

Character::~Character() { SDL_DestroyTexture(texture); }
