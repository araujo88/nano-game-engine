#include "../include/NPC.hpp"
#include "../include/game.hpp"
#include "../include/player.hpp"
#include "../include/world.hpp"

int main(void) {
  auto game = nano::Game("Nano Game Engine");

  auto renderer = game.getRenderer();

  auto world = nano::World(renderer, "sprites/grass.png");

  auto player = nano::Player("Player", WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2, 32,
                             renderer, "sprites/wojak.png");

  std::vector<nano::NPC *> npcs;

  for (int i = 0; i < 10; ++i)
    npcs.push_back(new nano::NPC("NPC", 0, 0, renderer, "sprites/chud.png"));

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