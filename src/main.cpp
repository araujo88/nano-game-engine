#include "../include/NPC.hpp"
#include "../include/game.hpp"
#include "../include/player.hpp"
#include "../include/world.hpp"

int main(void) {
  nano::Game game = nano::Game("Nano Game Engine");

  nano::World world = nano::World(game.getRenderer(), "sprites/grass.png");

  nano::Player player = nano::Player(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2, 10,
                                     game.getRenderer(), "sprites/player.png");

  std::vector<nano::NPC *> npcs;

  for (int i = 0; i < 10; ++i)
    npcs.push_back(new nano::NPC(game.getRenderer(), "sprites/angry_sun.png"));

  game.addEntity(&world);
  game.addEntity(&player);

  for (auto &npc : npcs)
    game.addEntity(npc);

  game.mainLoop();

  for (auto &npc : npcs) {
    delete npc;
  }
  npcs.clear();

  return 0;
}