#ifndef NPC_H_
#define NPC_H_

#include "character.hpp"
#include "constants.hpp"
#include <chrono>
#include <random>
#include <string>
#include <thread>

namespace nano {
class NPC : public Character {
private:
  const int max_speed = 20;
  std::random_device rd;
  Uint32 lastMoveTime = 0;

public:
  NPC(std::string name, int x, int y, SDL_Renderer *renderer,
      std::string spritePath);
  void move();
  void render(SDL_Renderer *renderer) override;
  void handleEvent(SDL_Event *event) override;
  void update() override;
  std::string getName() override;
  SDL_Rect getBoundingBox() override;
  void handleCollision() override;
  bool isColliding(const SDL_Rect &box) override;
  ~NPC() override = default;
};
} // namespace nano

#endif