cmake_minimum_required(VERSION 3.14)

#LANGUAGES can be: C , CXX (i.e. C++)
project(2D-rpg-game-engine VERSION 1.0
LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# To prevent Apple frameworks from being included before brew installed packages
include_directories(BEFORE /usr/local/include)
set(CMAKE_FIND_FRAMEWORK LAST) 

# SDL
find_package(SDL2_ttf REQUIRED)
find_package(SDL2_IMAGE REQUIRED)
find_package(SDL2 REQUIRED)

add_executable(game main.cpp)

# Link SDL to the library
target_link_libraries(game PUBLIC SDL2::SDL2main SDL2::SDL2 SDL2_image::SDL2_image SDL2_ttf::SDL2_ttf)

# Copy sprites to the build directory
file(COPY sprites/ DESTINATION ${CMAKE_BINARY_DIR}/sprites)