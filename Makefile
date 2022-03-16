SRC=src/main.c
BIN=hitagi
SDL_FLAGS=-lSDL2 -pthread -lSDL2_image 
COMPILER=gcc

all:
	$(COMPILER) $(SRC) -g $(SDL_FLAGS) -o $(BIN)
clean:
	rm $(BIN)