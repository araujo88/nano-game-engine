#ifndef NPC_H_
#define NPC_H_

#include "constants.hpp"
#include "entity.hpp"
#include <chrono>
#include <random>
#include <string>
#include <thread>

namespace nano {
class NPC : public IEntity {
private:
  int x, y;
  const int max_speed = 10;
  SDL_Texture *texture;
  std::string name;
  std::string spritePath;
  std::random_device rd;
  Uint32 lastMoveTime = 0;

public:
  NPC(SDL_Renderer *renderer, std::string spritePath);
  void move();
  void render(SDL_Renderer *renderer) override;
  void handleEvent(SDL_Event *event) override;
  void update() override;
  ~NPC();
};
} // namespace nano

#endif