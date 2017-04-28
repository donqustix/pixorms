CXX = g++
CXXFLAGS = -std=c++14 -pedantic -Wall -Wextra -Isrc
LDFLAGS = -lSDL2 -lSDL2_image -lSDL2_ttf

PROJECT_NAME = worms
PROJECT_SRCS = $(wildcard src/worms/*.cpp) $(wildcard src/worms/*/*.cpp)

all: $(PROJECT_SRCS)
	$(CXX) $(CXXFLAGS) $^ -o bin/$(PROJECT_NAME) $(LDFLAGS)

run:
	./bin/$(PROJECT_NAME)

bin/%.o: src/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

