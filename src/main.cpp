#include "../include/game.hpp"
#include "../include/player.hpp"
#include "../include/world.hpp"

int main(void) {
  nano::Game game = nano::Game("Nano Game Engine");

  nano::World world = nano::World(game.getRenderer(), "sprites/grass.png");

  nano::Player player = nano::Player(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2, 10,
                                     game.getRenderer(), "sprites/player.png");

  game.addEntity(&world);
  game.addEntity(&player);

  game.mainLoop();

  return 0;
}