#include "scoundrel.h"

int main(int argc, char ** argv) {
  Scoundrel::init_scoundrel("scoundrel.json");
  Scoundrel::game_loop();
  Scoundrel::deinitialize_game();
  return 0;
}


