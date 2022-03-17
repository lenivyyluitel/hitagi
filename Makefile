SRC=src/main.c
BIN=hitagi
SDL_FLAGS=-lSDL2 -pthread -lSDL2_image 
COMPILER=gcc

all:
	$(COMPILER) $(SRC) -g $(SDL_FLAGS) -DWITH_GPHOTO -Ilib/gifdec lib/gifdec/gifdec.c -o $(BIN)
clean:
	rm $(BIN)