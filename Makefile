CC=g++
INCLUDE=-I./include
CFLAGS=-lsfml-window -lsfml-system -lsfml-graphics -lsfml-audio -wALL -ljson -Qunused-arguments
# -I/Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX10.8.sdk/usr/include/python2.7
LIB_DIR=lib
SOURCE_DIR=src
OBJ_DIR=obj
LIB_FILE=libscoundrel.a
SOURCES=$(wildcard $(SOURCE_DIR)/*.cpp)
OBJS=$(SOURCES:$(SOURCE_DIR)/%.cpp=$(OBJ_DIR)/%.o)

all: $(LIB_FILE)

obj:
	mkdir -p $(OBJ_DIR)

lib:
	mkdir -p $(LIB_DIR)

$(OBJS): $(OBJ_DIR)/%.o : $(SOURCE_DIR)/%.cpp | obj
	@echo $<
	$(CC) $(INCLUDE) -c $< -o $@

$(LIB_FILE): $(OBJS) | lib
	mkdir -p $(LIB_DIR)
	$(CC) -c $(CFLAGS) -fPIC
	$(CC) -shared -o $(LIB_DIR)/$(LIB_FILE) $(OBJS) $(CFLAGS)

.PHONY: clean

clean:
	-rm $(OBJ_DIR)/*.o
	-rm $(LIB_DIR)/$(LIB_FILE)
