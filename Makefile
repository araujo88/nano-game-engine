CXX = g++
CXXFLAGS = -Wall -Wextra -Wpedantic
LDLIBS = -lSDL2 -lSDL2_image -lSDL2_mixer -lSDL2_ttf

all: game

game: main.cpp
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDLIBS)

run:
	./game

clean:
	rm -rf game
