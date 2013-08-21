CC=g++
CFLAGS=-I./include -lsfml-window -lsfml-system -lsfml-graphics
SOURCES=src/player.cpp src/scoundrel.cpp src/entity.cpp src/rect.cpp src/tile.cpp

all:
	$(CC) -o ./bin/scoundrel $(CFLAGS) $(SOURCES)
