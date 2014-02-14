#include "scoundrel.h"

int main(int argc, char ** argv) {
  Scoundrel::init_scoundrel(800, 600);
  Scoundrel::game_loop();

  // re-init the demo as a basic scroll map with a sprite that wanders around
  // animated.
  Scoundrel::deinitialize_game();
  return 0;
}


