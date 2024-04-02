cmake_minimum_required(VERSION 3.14)

#LANGUAGES can be: C , CXX (i.e. C++)
project(nano-game-engine VERSION 1.0
LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

file(GLOB SOURCES "src/*.cpp")

# Choose one of the following depending on your needs
add_library(nano-game-engine STATIC ${SOURCES})
# add_library(nano-game-engine SHARED ${SOURCES})

target_include_directories(nano-game-engine PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

# Optional: Set version properties for shared libraries
if(BUILD_SHARED_LIBS)
    set_target_properties(nano-game-engine PROPERTIES
        VERSION ${PROJECT_VERSION}
        SOVERSION ${PROJECT_VERSION_MAJOR}
    )
endif()

# Optional: Install rules
install(TARGETS nano-game-engine
    ARCHIVE DESTINATION lib
    LIBRARY DESTINATION lib
    RUNTIME DESTINATION bin # For Windows DLLs
)
install(DIRECTORY include/ DESTINATION include)

# To prevent Apple frameworks from being included before brew installed packages
include_directories(BEFORE /usr/local/include)

include_directories(${SDL2_INCLUDE_DIRS})

set(CMAKE_FIND_FRAMEWORK LAST) 

# SDL
find_package(SDL2_ttf REQUIRED)
find_package(SDL2_IMAGE REQUIRED)
find_package(SDL2 REQUIRED)

add_executable(game ${SOURCES})

# Link SDL to the library
target_link_libraries(game PRIVATE SDL2::SDL2main SDL2::SDL2 SDL2_image::SDL2_image SDL2_ttf::SDL2_ttf)

# Copy sprites to the build directory
file(COPY sprites/ DESTINATION ${CMAKE_BINARY_DIR}/sprites)
