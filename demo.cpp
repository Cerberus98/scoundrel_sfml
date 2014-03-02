#include <iostream>

#include "linked_list.h"
#include "scoundrel.h"
#include "os.h"
#include "tile_layer.h"
#include "types.h"


class Demo : public Scoundrel::FrameHandler {
  void frame_start() {
  }

  void frame_end(Scoundrel::U64 elapsed) {
  }

};



int main(int argc, char ** argv) {
  Scoundrel::LinkedList<Scoundrel::U32> list;
  list.append(1);
  list.append(2);
  list.append(3);
  list.append(4);
  list.append(5);
  list.print();


  Scoundrel::init_scoundrel(800, 600, 60);
  Demo demo;

  //TODO: Load resources here

  Scoundrel::TileLayer tile_layer;

  Scoundrel::insert_layer(&tile_layer, 0);
  Scoundrel::set_frame_handler(&demo);
  Scoundrel::game_loop();

  // re-init the demo as a basic scroll map with a sprite that wanders around
  // animated.
  Scoundrel::deinitialize_game();
  return 0;
}


