#include <iostream>

#include "scoundrel.h"
#include "os.h"


class Demo : public Scoundrel::Scoundrel {
  void frame_start() {
  }

  void frame_end() {
  }

};



int main(int argc, char ** argv) {
  Scoundrel::init_scoundrel(800, 600, 60);
  Demo demo;
  Scoundrel::set_game_handler(&demo);
  Scoundrel::game_loop();

  // re-init the demo as a basic scroll map with a sprite that wanders around
  // animated.
  Scoundrel::deinitialize_game();
  return 0;
}


