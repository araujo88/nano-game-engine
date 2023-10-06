#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <iostream>
#include <list>

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 800

#define DEBUG(s) std::cout << s << std::endl;

// Define game constants
const int TILE_SIZE = 32;
const int TILES_X = WINDOW_WIDTH / TILE_SIZE;
const int TILES_Y = WINDOW_HEIGHT / TILE_SIZE;
const int WORLD_WIDTH = 100;  // Example: 100 tiles width
const int WORLD_HEIGHT = 100; // Example: 100 tiles height

class IEntity {
public:
  virtual void render(SDL_Renderer *renderer) = 0;
  virtual void handleEvent(SDL_Event *event) = 0;
};

class Game {
private:
  SDL_Window *window;
  SDL_Renderer *renderer;
  std::string title;
  SDL_Event event;
  std::list<IEntity *> entities;

public:
  bool isRunning = true;

  Game(std::string title) {
    title = title;

    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
      SDL_Log("Unable to initialize SDL: %s", SDL_GetError());
      exit(1);
    }

    window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_UNDEFINED,
                              SDL_WINDOWPOS_UNDEFINED, WINDOW_WIDTH,
                              WINDOW_HEIGHT, SDL_WINDOW_SHOWN);

    if (!window) {
      SDL_Log("Unable to create window: %s", SDL_GetError());
      exit(1);
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_SOFTWARE);
    if (!renderer) {
      SDL_Log("Unable to create renderer: %s", SDL_GetError());
      exit(1);
    }

    if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG)) {
      SDL_Log("Unable to initialize SDL_image: %s", IMG_GetError());
      exit(1);
    }
  }
  SDL_Renderer *getRenderer() { return renderer; }
  void clear() {
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
  }
  void update() { SDL_RenderPresent(renderer); }
  void handleEvents() {
    while (SDL_PollEvent(&event)) {
      if (event.type == SDL_QUIT) {
        isRunning = false;
      }
      for (auto &entity : entities) {
        entity->handleEvent(&event);
      }
    }
  }
  void addEntity(IEntity *entity) { entities.push_back(entity); }
  void renderEntities() {
    for (auto &entity : entities) {
      entity->render(renderer);
    }
  }
  void mainLoop() {
    while (isRunning) {
      handleEvents();
      clear();
      renderEntities();
      update();
    }
  }
  ~Game() {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
  }
};

class Player : public IEntity {
private:
  int x, y;
  int speed;
  SDL_Texture *texture;
  std::string name;
  std::string spritePath;

public:
  Player(int x, int y, int speed, SDL_Renderer *renderer,
         std::string spritePath)
      : x(x), y(y), speed(speed) {
    texture = IMG_LoadTexture(renderer, spritePath.c_str());
    if (!texture) {
      SDL_Log("Failed to load player texture: %s", IMG_GetError());
      exit(1);
    }
  };
  void moveUp() { y -= speed; }
  void moveDown() { y += speed; }
  void moveLeft() { x -= speed; }
  void moveRight() { x += speed; }
  void render(SDL_Renderer *renderer) {
    SDL_Rect playerRect = {x, y, TILE_SIZE, TILE_SIZE};
    SDL_RenderCopy(renderer, texture, NULL, &playerRect);
  }
  void handleEvent(SDL_Event *event) {
    if (event->type == SDL_KEYDOWN) {
      switch (event->key.keysym.sym) {
      case SDLK_UP:
        moveUp();
        break;
      case SDLK_DOWN:
        moveDown();
        break;
      case SDLK_LEFT:
        moveLeft();
        break;
      case SDLK_RIGHT:
        moveRight();
        break;
      }
    }
  }
  ~Player() { SDL_DestroyTexture(texture); }
};

class World : public IEntity {
private:
  enum TileType {
    TILE_GRASS = 0,
    TILE_WATER,
    TILE_ROAD,
  };
  int tiles[WORLD_WIDTH][WORLD_HEIGHT];
  SDL_Texture *grassTexture; // As an example

public:
  World(SDL_Renderer *renderer, std::string spritePath) {
    // Initialize the world tiles (for now, let's say everything is grass)
    for (int i = 0; i < WORLD_WIDTH; i++) {
      for (int j = 0; j < WORLD_HEIGHT; j++) {
        tiles[i][j] = TILE_GRASS;
      }
    }

    // Load grass texture
    grassTexture = IMG_LoadTexture(renderer, spritePath.c_str());
    if (!grassTexture) {
      SDL_Log("Failed to load grass texture: %s", IMG_GetError());
      exit(1);
    }
  }

  void render(SDL_Renderer *renderer) {
    for (int i = 0; i < TILES_X; ++i) {
      for (int j = 0; j < TILES_Y; ++j) {
        SDL_Rect dest = {i * TILE_SIZE, j * TILE_SIZE, TILE_SIZE, TILE_SIZE};

        // Render based on the tile type
        switch (tiles[i][j]) {
        case TILE_GRASS:
          SDL_RenderCopy(renderer, grassTexture, NULL, &dest);
          break;
          // ... other tiles
        }
      }
    }
  }

  void handleEvent(SDL_Event *event) {
    // Handle any world-specific events (for now, do nothing)
  }

  ~World() {
    SDL_DestroyTexture(grassTexture);
    // Destroy other textures if added
  }
};

int main(void) {
  Game game = Game("2D RPG Game Engine");

  World world = World(game.getRenderer(), "sprites/grass.png");

  Player player = Player(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2, 10,
                         game.getRenderer(), "sprites/player.png");

  game.addEntity(&world);
  game.addEntity(&player);

  game.mainLoop();

  return 0;
}