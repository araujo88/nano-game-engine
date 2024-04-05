#ifndef PROJECTILE_H_
#define PROJECTILE_H_

#include "character.hpp"
#include "constants.hpp"
#include <string>

namespace nano {
class Projectile : public Character {
private:
  const int speed = 20;
  Direction direction;
  Uint32 lastMoveTime = 0;

public:
  Projectile(std::string name, int x, int y, SDL_Renderer *renderer,
             std::string spritePath, Direction direction);
  void move();
  void render(SDL_Renderer *renderer) override;
  void handleEvent(SDL_Event *event) override;
  void update() override;
  std::string getName() override;
  SDL_Rect getBoundingBox() override;
  void handleCollision(IEntity *entity) override;
  bool isColliding(const SDL_Rect &box) override;
  bool isOutOfBounds();
  ~Projectile() override;
};
} // namespace nano

#endif