#ifndef CHARACTER_H_
#define CHARACTER_H_

#include "constants.hpp"
#include "entity.hpp"
#include <chrono>
#include <random>
#include <string>
#include <thread>

namespace nano {
class Character : public IEntity {
protected:
  int x = 0, y = 0;
  SDL_Texture *texture;
  std::string spritePath;

public:
  Character(std::string name, int x, int y, SDL_Renderer *renderer,
            std::string spritePath);
  void render(SDL_Renderer *renderer) override;
  void handleEvent(SDL_Event *event) override;
  void update() override;
  bool isColliding(const SDL_Rect &box) override;
  virtual ~Character();
  std::string getName() override;
  SDL_Rect getBoundingBox() override;
  void handleCollision() override;
};
} // namespace nano
#endif