#include <iostream>
#include <cstdio>
#include "linked_list.h"
#include "scoundrel.h"
#include "os.h"
#include "tile_layer.h"
#include "types.h"
#include "asset.h"


class Demo : public Scoundrel::FrameHandler {
  void frame_start() {
  }

  void frame_end(Scoundrel::U64 elapsed) {
  }

};


void test_resource_loading() {
  Scoundrel::Asset asset("the-name-is-known", "/Users/john6414/code/scoundrel_sfml/src/resources/tree.png");
  asset.load_asset();
}

int main(int argc, char ** argv) {
  

  
  Scoundrel::init_scoundrel(800, 600, 60);
  Demo demo;

  //TODO: Load resources here
  test_resource_loading();

  Scoundrel::TileLayer tile_layer;

  Scoundrel::insert_layer(&tile_layer, 0);
  Scoundrel::set_frame_handler(&demo);
  Scoundrel::game_loop();

  // re-init the demo as a basic scroll map with a sprite that wanders around
  // animated.
  Scoundrel::deinitialize_game();
  return 0;
}


