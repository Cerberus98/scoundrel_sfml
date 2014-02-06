CC=g++
CFLAGS=-I./include -lsfml-window -lsfml-system -lsfml-graphics -lsfml-audio -wALL -ljson -Qunused-arguments
# -I/Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX10.8.sdk/usr/include/python2.7
LIB_DIR=lib/
SOURCE_DIR=src/
OBJ_DIR=obj/
SOURCE_FILES=player.cpp scoundrel.cpp entity.cpp rect.cpp tile.cpp camera.cpp animation.cpp collidable.cpp game_map.cpp level_loader.cpp
OBJS=$(SOURCE_FILES:%.cpp=$(OBJ_DIR)%.o)
LIB_FILE=libscoundrel.a


all: $(LIB_FILE)

obj:
	mkdir -p $(OBJ_DIR)

$(OBJ_DIR)%.o: $(SOURCE_DIR)%.cpp
	$(CC) $(CFLAGS) -c $< -o $@

$(LIB_FILE): $(OBJS)
	mkdir -p $(LIB_DIR)
	$(CC) -c $(CFLAGS) $(OBJS) -fPIC
	$(CC) -shared -o $(LIB_DIR)$(LIB_FILE) $(OBJS) $(CFLAGS)

clean:
	rm $(OBJ_DIR)*.o
	rm $(LIB_DIR)$(LIB_FILE)
