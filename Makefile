CC=g++
CFLAGS=-I./include -lsfml-window -lsfml-system -lsfml-graphics -lsfml-audio -wALL -ljson
SOURCES=src/player.cpp src/scoundrel.cpp src/entity.cpp src/rect.cpp src/tile.cpp src/camera.cpp src/animation.cpp src/battery.cpp src/collidable.cpp src/game_map.cpp src/level_loader.cpp src/exit_arrow.cpp
CONFIG_LIB_O=obj/color.o obj/configitem_base.o obj/configfile.o

all:
	$(CC) -o ./bin/scoundrel $(CFLAGS) $(SOURCES)
