#include <iostream>

#include "linked_list.h"
#include "scoundrel.h"
#include "os.h"
#include "shape_drawable.h"
#include "tile_layer.h"
#include "types.h"


class Demo : public Scoundrel::FrameHandler {
  void frame(Scoundrel::U64 elapsed) {
  }
};

void test_linked_list() {
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

  std::cout << std::endl;
  Scoundrel::LinkedList<Scoundrel::U32>::iter list_iter = list.get_iterator();

  list_iter.next(); //Should be deleting the head node
  list.delete_node(list_iter.current);
  list.print();
  std::cout << std::endl;

  for (int i = 0; i<6; ++i)
    list_iter.next();
  list.delete_node(list_iter.current); //Should be deleting the last node
  list.print();

  std::cout << std::endl;
}

int main(int argc, char ** argv) {
  Scoundrel::init_scoundrel(800, 600, 60);
  Demo demo;

  //TODO: Load resources here

  Scoundrel::TileLayer tile_layer(800, 600);
  Scoundrel::Tile tile;
  Scoundrel::RectangleDrawable rect(32, 32);

  tile.set_drawable(&rect);

  //TODO this won't be how it really works. We might pass a reference to a 2D array or something
  tile_layer.add_tile(&tile);

  Scoundrel::insert_layer(&tile_layer, 0);
  Scoundrel::set_frame_handler(&demo);
  Scoundrel::game_loop();

  // re-init the demo as a basic scroll map with a sprite that wanders around
  // animated.
  Scoundrel::deinitialize_game();
  return 0;
}


