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
#include <SFML/Window.hpp>

#include "animation.h"
#include "collidable.h"
#include "core.h"
#include "camera.h"
#include "game_map.h"
#include "player.h"
#include "scoundrel_utils.h"
#include "tile.h"
#include "tile_helper.h"


namespace Scoundrel {
  enum game_modes {GAME_PLAY, GAME_END, GAME_WIN, GAME_NEXT_LEVEL, GAME_MAP_EDIT};

  //TODO: move away from all the globals.
  const float WALK = 0.25f;
  const float MAX_WALK = 4.f;
  const float WALK_STOP = 4.f;
  const int MOVE_DELTA = MAX_WALK;
  const float JUMP_SPEED = -18.5f;

  const float GRAVITY = 1.6f;
  const float TERMINAL_VELOCITY = 15.f;
  const int TILE_WIDTH = 32, TILE_HEIGHT = 32;
  const int NUM_ANIMATIONS=20;

  // Impleent a camera/view class
  int WINDOW_WIDTH, WINDOW_HEIGHT;
  const float CAMERA_SNAP_X = 0.2f, CAMERA_SNAP_Y = 0.23f;
  const int FRAMERATE_LIMIT = 60;
  std::string proc_path;

  void load_config(int argc, char ** argv);
  void init_game();
  void game_loop(sf::RenderWindow * window);
  void deinitialize_game(sf::RenderWindow * window);
  sf::RenderWindow* init_sfml();

}
