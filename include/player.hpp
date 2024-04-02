#ifndef PLAYER_H_
#define PLAYER_H_

#include "constants.hpp"
#include "entity.hpp"
#include <string>

namespace nano {
class Player : public IEntity {
private:
  int x, y;
  int speed;
  SDL_Texture *texture;
  std::string name;
  std::string spritePath;

public:
  Player(int x, int y, int speed, SDL_Renderer *renderer,
         std::string spritePath);
  void moveUp();
  void moveDown();
  void moveLeft();
  void moveRight();
  void render(SDL_Renderer *renderer) override;
  void handleEvent(SDL_Event *event) override;
  ~Player();
};
} // namespace nano

#endif