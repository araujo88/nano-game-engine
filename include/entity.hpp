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
public:
  virtual void render(SDL_Renderer *renderer) = 0;
  virtual void handleEvent(SDL_Event *event) = 0;
};
} // namespace nano

#endif