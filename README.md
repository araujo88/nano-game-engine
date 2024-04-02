# 2D Game Engine

A simple 2D game engine built using the SDL2 library. This engine provides basic functionalities like player movement, world rendering, and a modular entity system to ease the addition of new in-game objects and features.

## Features

- Basic player character with 4-directional movement.
- Simple world/tile rendering system.
- Modular entity system: Easily add new game objects or features by implementing the `IEntity` interface.
- Event handling for all entities.
- Easily extendable for more complex game mechanics.

## Dependencies

- [SDL2](https://www.libsdl.org/)
- [SDL2_image](https://www.libsdl.org/projects/SDL_image/)
- [SDL2_ttf](https://www.libsdl.org/projects/SDL_ttf/) (if text rendering is added in future)

## Getting Started

### Installation

1. First, ensure you have the SDL2, SDL2_image, and SDL2_ttf libraries installed.
2. Clone this repository:
   ```bash
   git clone https://github.com/araujo88/2d-rpg-game-engine.git
   ```
3. Navigate to the project directory and compile the game:
   ```bash
   mkdir build
   cd build
   cmake ..
   make
   ```
4. Run the compiled game:
   ```bash
   ./game # in your build folder
   ```

### Usage

Use the arrow keys (`↑`, `↓`, `←`, `→`) to move the player character around the world. You can easily extend the game by adding more entities or features using the provided `IEntity` interface.

## Contributing

If you would like to contribute to the development of this 2D RPG Game Engine, please:

1. Read the `TODOs` documentation.
2. Fork the repository.
3. Create your feature branch (`git checkout -b feature/YourFeature`).
4. Commit your changes (`git commit -am 'Add YourFeature'`).
5. Push to the branch (`git push origin feature/YourFeature`).
6. Create a new pull request.

## License

This project is licensed under the MIT License. See the `LICENSE` file for details.
