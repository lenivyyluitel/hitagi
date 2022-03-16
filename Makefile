all:
	gcc main.c -g -lSDL2 -pthread -lSDL2_image -o hitagi
clean:
	rm binary