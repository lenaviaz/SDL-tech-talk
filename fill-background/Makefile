#easy sample Makefile


CC = gcc

#compiler flags
CFLAGS = -g -Wall -fsanitize=address -static-libasan

TARGET = hellomake

$(TARGET) : main.c
	$(CC) $(CFLAGS) -o $(TARGET) main.c functions.c characters.c `sdl2-config --cflags --libs` -lSDL2 -lSDL2_image





# hellomake: main.c
# 	gcc -o hellomake main.c -I.
