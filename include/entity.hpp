#ifndef ENTITY_H_
#define ENTITY_H_

#include "constants.hpp"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <iostream>
#include <list>

namespace nano {
class IEntity {
protected:
  SDL_Rect boundingBox;
  std::string name;

public:
  virtual void render(SDL_Renderer *renderer) = 0;
  virtual void handleEvent(SDL_Event *event) = 0;
  virtual void update() = 0;
  virtual bool isColliding(const SDL_Rect &box) = 0;
  virtual std::string getName() = 0;
  virtual SDL_Rect getBoundingBox() = 0;
  virtual void handleCollision() = 0;
};
} // namespace nano

#endif