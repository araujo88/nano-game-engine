# Nano Game Engine

A simple 2D game engine built using the SDL2 library. This engine provides foundational functionalities for creating 2D games, including player movement, world rendering, and a modular entity system to facilitate the addition of new in-game objects and mechanics.

## Features

- Basic player character with 4-directional movement.
- Simple world/tile rendering system.
- Modular entity system: Easily add new game objects or mechanics by implementing the `IEntity` interface.
- Event handling for all entities, enabling interaction and response to player inputs or other game events.
- Collision detection to handle interactions between entities.
- Easily extendable architecture for developing more complex game features.

## Class Hierarchy

- **IEntity**: Base interface for all entities in the game, providing a contract for rendering, event handling, and updating logic.
  - **Character**: Abstract base class for movable entities, extending `IEntity` with common attributes like position, texture, and collision detection.
    - **Player**: Represents the player character, implementing specific movement logic and player-related functionalities.
    - **NPC**: Non-player characters with potential for AI behaviors, quest interactions, or other game mechanics.
  - **World**: Handles the rendering of the game environment, such as tiles or static background elements, implementing the `IEntity` interface to fit within the game's update and rendering loop.

## Dependencies

- [SDL2](https://www.libsdl.org/)
- [SDL2_image](https://www.libsdl.org/projects/SDL_image/)
- [SDL2_ttf](https://www.libsdl.org/projects/SDL_ttf/) (optional, for future text rendering features)

## Getting Started

### Installation

1. Ensure the SDL2, SDL2_image, and SDL2_ttf libraries are installed on your system.
2. Clone the repository:
   ```bash
   git clone https://github.com/araujo88/nano-game-engine.git
   ```
3. Navigate to the project directory and compile the game:
   ```bash
   mkdir build
   cd build
   cmake ..
   make
   ```
4. Execute the compiled game binary:
   ```bash
   ./game # from within the build folder
   ```

### Usage

- Navigate the player character using the arrow keys (`↑`, `↓`, `←`, `→`).
- Extend the game by creating new subclasses of `IEntity` or `Character` for diverse gameplay elements.
- Implement custom behaviors for NPCs or interactive world elements to enrich the game environment.

## Contributing

Contributions are welcome to enhance and expand the Nano Game Engine:

1. Review the `TODOs` documentation for areas of potential improvement.
2. Fork the repository.
3. Create a feature branch (`git checkout -b feature/AmazingFeature`).
4. Commit your changes (`git commit -am 'Add some AmazingFeature'`).
5. Push to the branch (`git push origin feature/AmazingFeature`).
6. Open a pull request.

## License

This project is released under the MIT License - see the `LICENSE` file for details.
