#ifndef GAME_H_
#define GAME_H_

#include "constants.hpp"
#include "entity.hpp"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <algorithm>
#include <iostream>
#include <list>
#include <memory>

namespace nano {
class Game {
private:
  SDL_Window *window;
  SDL_Renderer *renderer;
  std::string title;
  SDL_Event event;
  std::list<IEntity *> entities;

public:
  bool isRunning = true;

  Game(std::string title);
  SDL_Renderer *getRenderer();
  void clear();
  void update();
  void handleEvents();
  void mainLoop();
  void addEntity(IEntity *entity);
  void renderEntities();
  ~Game();
};
} // namespace nano

#endif