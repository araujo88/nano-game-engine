#ifndef PLAYER_H_
#define PLAYER_H_

#include "character.hpp"
#include "constants.hpp"
#include "projectile.hpp"
#include <algorithm>
#include <memory>
#include <string>
#include <vector>

namespace nano {
class Player : public Character {
private:
  int speed;
  bool isFacingUp;
  bool isFacingDown;
  bool isFacingRight;
  bool isFacingLeft;
  SDL_Renderer *renderer;
  std::vector<std::unique_ptr<Projectile>> bullets;

public:
  Player(std::string name, SDL_Renderer *renderer, std::string spritePath);
  Player(std::string name, int x, int y, int speed, SDL_Renderer *renderer,
         std::string spritePath);
  void moveUp();
  void moveDown();
  void moveLeft();
  void moveRight();
  void render(SDL_Renderer *renderer) override;
  void handleEvent(SDL_Event *event) override;
  void update() override;
  std::string getName() override;
  SDL_Rect getBoundingBox() override;
  void handleCollision(IEntity *entity) override;
  bool isColliding(const SDL_Rect &box) override;
  void attack();
  ~Player() override = default;
};
} // namespace nano

#endif