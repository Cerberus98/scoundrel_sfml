#include <fstream>
#include <json/json.h>
#include <iostream>
#include <list>
#include <map>
#include <sstream>
#include <string>
#include <stdlib.h>
#include <unistd.h>

//#include <Python.h>

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>

#include "animation.h"
#include "clock.h"
#include "collidable.h"
#include "core.h"
#include "camera.h"
#include "game_map.h"
#include "layer.h"
#include "player.h"
#include "scoundrel_utils.h"
#include "tile.h"
#include "tile_helper.h"
#include "types.h"


namespace Scoundrel {
  class FrameHandler {
  public:
    virtual void frame_start() = 0;
    virtual void frame_end(U64 elapsed) = 0;
  };

  enum game_modes {GAME_PLAY, GAME_END, GAME_WIN, GAME_NEXT_LEVEL, GAME_MAP_EDIT};
  //TODO: move these into core/universe later
  Clock game_clock;
  U64 runtime;

  int WINDOW_WIDTH, WINDOW_HEIGHT;
  const float CAMERA_SNAP_X = 0.2f, CAMERA_SNAP_Y = 0.23f;

  void load_config(int argc, char ** argv);
  void init_scoundrel(std::string path);
  void init_scoundrel(int window_width, int window_height, int framerate);
  void set_frame_handler(FrameHandler* game);

  // Returns elapsed time of last frame
  void game_loop();

  void deinitialize_game();
  sf::RenderWindow* init_sfml(std::string path);

  void insert_layer(Layer* layer, U32 index);
  Layer* get_layer(U32 index);

  //TODO: add an elapsed circular queue so we can get a running average framerate
  int max_framerate;
  U64 frame_time;
  FrameHandler * _game;

  //TODO: this should really be a linked list, but this is for testing
  Layer* _layer;
}

