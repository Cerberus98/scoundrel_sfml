#include <iostream>

#include "camera.h"
#include "linked_list.h"
#include "scoundrel.h"
#include "os.h"
#include "shape_drawable.h"
#include "scoundrel_utils.h"
#include "tile_layer.h"
#include "types.h"


class Demo : public Scoundrel::FrameHandler {
  void frame(Scoundrel::U64 elapsed) {
    Scoundrel::KeyState key_state = Scoundrel::get_key_state();
    Scoundrel::Camera* camera = Scoundrel::get_camera();
    if (key_state.left_pressed)
      camera->move(-2, 0);

    if (key_state.right_pressed)
      camera->move(2, 0);

    if (key_state.up_pressed)
      camera->move(0, -2);

    if (key_state.down_pressed)
      camera->move(0, 2);
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


void init_map(Scoundrel::Tile***& game_map, Scoundrel::Tile* tile_registry, Scoundrel::U32 map_width, Scoundrel::U32 map_height) {
  Scoundrel::U32 toggle = 0;
  game_map = new Scoundrel::Tile**[map_height];
  for (int i = 0; i < map_height; ++i) {
    game_map[i] = new Scoundrel::Tile*[map_width];
    for (int j = 0; j < map_width; ++j) {
      game_map[i][j] = &tile_registry[toggle];
      toggle ^= 1;
    }
    toggle ^= 1;
  }
}

int main(int argc, char ** argv) {
  Scoundrel::U32 screen_width = 800;
  Scoundrel::U32 screen_height = 600;
  Scoundrel::U32 tile_width = 32;
  Scoundrel::U32 tile_height = 32;

  Scoundrel::U32 map_width = (screen_width * 4) / tile_width;
  Scoundrel::U32 map_height = (screen_height * 3) / tile_height;

  Scoundrel::Tile tile_registry[2];
  Scoundrel::Tile*** game_map;
  Scoundrel::TileLayer tile_layer(tile_width, tile_height);
  Scoundrel::RectangleDrawable green_rect(32, 32, sf::Color::Green);
  Scoundrel::RectangleDrawable yellow_rect(32, 32, sf::Color::Yellow);
  Scoundrel::Camera camera;
  camera.set_window_size(screen_width, screen_height);
  camera.set_absolute(-2, -2);

  tile_registry[0].set_drawable(&green_rect);
  tile_registry[1].set_drawable(&yellow_rect);

  init_map(game_map, tile_registry, map_width, map_height);

  Scoundrel::init_scoundrel(800, 600, 60);
  Demo demo;
  //TODO: Load resources here

  tile_layer.attach_map(game_map, map_width, map_height);
  Scoundrel::insert_layer(&tile_layer, 0);
  Scoundrel::set_camera(&camera);
  Scoundrel::set_frame_handler(&demo);
  Scoundrel::game_loop();

  for (int i = 0; i < map_height; ++i) {
    delete game_map[i];
  }
  delete game_map;

  Scoundrel::deinitialize_game();

  return 0;
}


