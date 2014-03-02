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
  list.insert(0, 0);
  list.print();
  std::cout << std::endl;
  list.remove(0);
  list.print();

  std::cout << std::endl;
  list.append(1);
  list.append(2);
  list.append(3);
  list.append(4);
  list.append(5);
  list.print();

  std::cout << std::endl;
  list.insert(10, 0);
  list.print();

  std::cout << std::endl;
  list.insert(20, 6);
  list.print();

  std::cout << std::endl;
  list.remove(0);
  list.print();

  std::cout << std::endl;
  list.append(300);
  list.print();

  Scoundrel::LinkedList<Scoundrel::U32>::iter list_iter = list.get_iterator();
  do {
    std::cout << list_iter.data() << " ";
  } while (list_iter.next());
  std::cout << std::endl;

  Scoundrel::init_scoundrel(800, 600, 60);
  Demo demo;

  //TODO: Load resources here

  Scoundrel::TileLayer tile_layer;

  //Scoundrel::insert_layer(&tile_layer, 0);
  Scoundrel::set_frame_handler(&demo);
  Scoundrel::game_loop();

  // re-init the demo as a basic scroll map with a sprite that wanders around
  // animated.
  Scoundrel::deinitialize_game();
  return 0;
}


