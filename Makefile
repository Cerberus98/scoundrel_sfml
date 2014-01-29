CC=g++
CFLAGS=-I./include -lsfml-window -lsfml-system -lsfml-graphics -lsfml-audio -wALL -ljson -Qunused-arguments
# -I/Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX10.8.sdk/usr/include/python2.7
SOURCES=src/player.cpp src/scoundrel.cpp src/entity.cpp src/rect.cpp src/tile.cpp src/camera.cpp src/animation.cpp src/collidable.cpp src/game_map.cpp src/level_loader.cpp

all:
	mkdir -p ./bin
	$(CC) -o ./bin/scoundrel $(CFLAGS) $(SOURCES)
