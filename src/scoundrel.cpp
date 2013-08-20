#include <iostream>

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

#include "player.h"
#include "scoundrel_utils.h"
#include "tile.h"


//TODO: move away from all the globals. 
const int MOVE_DELTA = 2;
const int MAP_WIDTH = 100, MAP_HEIGHT = 100;
const int WINDOW_WIDTH = 800, WINDOW_HEIGHT = 600;
const int TILE_WIDTH = 32, TILE_HEIGHT = 32;
const float CAMERA_SNAP_X = 0.2f, CAMERA_SNAP_Y = 0.15f;
const int CAMERA_SNAP_LEFT = int(float(WINDOW_WIDTH) * CAMERA_SNAP_X);
const int CAMERA_SNAP_RIGHT = int(float(WINDOW_WIDTH) * (1.0f - CAMERA_SNAP_X));
const int CAMERA_SNAP_TOP = int(float(WINDOW_HEIGHT) * CAMERA_SNAP_Y);
const int CAMERA_SNAP_BOTTOM = int(float(WINDOW_HEIGHT) * (1.0f - CAMERA_SNAP_Y));

Tile*** game_map; //OH GOD
sf::Sprite* sprites;
sf::Texture* textures;

Point camera;
Player* player;

Point toTileCoords(Point pos) {
  Point tile_coords;
  tile_coords.x = pos.x / TILE_WIDTH;
  tile_coords.y = pos.y / TILE_HEIGHT;
  return tile_coords;
}

Point fromTileCoords(Point pos) {
  Point world_coords;
  world_coords.x = pos.x * TILE_WIDTH;
  world_coords.y = pos.y * TILE_HEIGHT;
  return world_coords;
}

Point fromTileCoords(int x, int y) {
  Point world_coords;
  world_coords.x = x * TILE_WIDTH;
  world_coords.y = y * TILE_HEIGHT;
  return world_coords;
}

sf::Texture load_image(std::string image_path) {
  sf::Texture tex;
  if (!tex.loadFromFile(image_path)) {
    std::cout << "Failed to load " << image_path << std::endl;
  }
  return tex;
}

void init_map()
{
  game_map = new Tile**[MAP_WIDTH];
  for (int i=0; i <MAP_WIDTH; ++i) {
    game_map[i] = new Tile*[MAP_HEIGHT];
    for (int j=0; j < MAP_HEIGHT; j++) {
      int rand_tile = rand() % 3;
      Tile* tile = new Tile(&sprites[rand_tile], i, j);
      if (rand_tile == 2)
        tile->set_passable(false);
      game_map[i][j] = tile;
    }
  }
}

void unload_map() {
  for (int i=0; i <MAP_HEIGHT; ++i) {
    delete game_map[i];
  }
  delete[] game_map;
}

void dump_map() {
  for (int i=0; i < MAP_HEIGHT; ++i) {
    for (int j=0; j < MAP_WIDTH; ++j) {
      std::cout << game_map[j][i] << " ";
    }
    std::cout << std::endl;
  }
}

sf::RenderWindow* init_sfml() {
  sf::RenderWindow* game_window = new sf::RenderWindow();
  game_window->create(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Scoundrel");
  return game_window;
}

void init_game()
{
  sprites = new sf::Sprite[5];
  textures = new sf::Texture[5];
  textures[0] = load_image("grass_32.jpg");
  sprites[0].setTexture(textures[0]);

  textures[1] = load_image("dirt_32.png");
  sprites[1].setTexture(textures[1]);

  textures[2] = load_image("tree.png");
  sprites[2].setTexture(textures[2]);

  textures[3] = load_image("player.png");
  sprites[3].setTexture(textures[3]);

  //TODO Make this go away
  player = new Player(&sprites[3], Point(300, 300), Rectangle(2, 4, 24, 30));
}

void deinitialize_game(sf::RenderWindow* window) {
  delete window;
  delete player;
  delete[] textures;
  delete[] sprites;
}

void check_and_move_camera() {
  Point absolute_coords;
  Point player_coords = player->position();
  absolute_coords.x = player_coords.x - camera.x;
  absolute_coords.y = player_coords.y - camera.y;

  if (absolute_coords.x <= CAMERA_SNAP_LEFT) {
    camera.x -= MOVE_DELTA;
  } else if (absolute_coords.x >= CAMERA_SNAP_RIGHT) {
    camera.x += MOVE_DELTA;
  }

  if (absolute_coords.y <= CAMERA_SNAP_TOP) {
    camera.y -= MOVE_DELTA;
  } else if (absolute_coords.y >= CAMERA_SNAP_BOTTOM) {
    camera.y += MOVE_DELTA;
  }
}

bool player_collide_vertical(Point left, Point right) {
  Point player_tile_left = toTileCoords(left);
  if (player_tile_left.y < 0 || player_tile_left.y > MAP_HEIGHT)
    return true;

  Point player_tile_right = toTileCoords(right);

  //Generalized form. Check all tiles that touch the segment top left of the player to top right
  for (int i = (int)player_tile_left.x; i <= (int)player_tile_right.x; ++i) {
    if (!game_map[i][int(player_tile_left.y)]->passable())
      return true;
  }
  return false;
}

bool player_collide_horizontal(Point top, Point bottom) {
  Point player_tile_top = toTileCoords(top);
  if (player_tile_top.x < 0 || player_tile_top.x > MAP_WIDTH)
    return true;

  Point player_tile_bottom = toTileCoords(bottom);
  for (int i = (int)player_tile_top.y; i <= (int)player_tile_bottom.y; ++i) {
    if (!game_map[int(player_tile_top.x)][i]->passable())
      return true;
  }
  return false;
}

void player_move_up(int delta) {
  Rectangle player_rect = player->get_bounding_rect();

  Point player_left_coords(player_rect.left(), player_rect.top());
  Point player_right_coords(player_rect.right(), player_rect.top());
  Point player_delta_left(player_left_coords.x, player_left_coords.y + delta);
  Point player_delta_right(player_right_coords.x, player_right_coords.y + delta);

  if (player_collide_vertical(player_delta_left, player_delta_right))
    return;

  player->move(0, delta);
  check_and_move_camera();
}

void player_move_down(int delta) {
  Rectangle player_rect = player->get_bounding_rect();

  Point player_left_coords(player_rect.left(), player_rect.bottom());
  Point player_right_coords(player_rect.right(), player_rect.bottom());
  Point player_delta_left(player_left_coords.x, player_left_coords.y + delta);
  Point player_delta_right(player_right_coords.x, player_right_coords.y + delta);

  if (player_collide_vertical(player_delta_left, player_delta_right))
    return;

  player->move(0, delta);
  check_and_move_camera();
}

void player_move_left(int delta) {
  Rectangle player_rect = player->get_bounding_rect();

  Point player_top_coords(player_rect.left(), player_rect.top());
  Point player_bottom_coords(player_rect.left(), player_rect.bottom());
  Point player_delta_top(player_top_coords.x + delta, player_top_coords.y);
  Point player_delta_bottom(player_bottom_coords.x + delta, player_bottom_coords.y);

  if (player_collide_horizontal(player_delta_top, player_delta_bottom))
    return;

  player->move(delta, 0);
  check_and_move_camera();
}

void player_move_right(int delta) {
  Rectangle player_rect = player->get_bounding_rect();

  Point player_top_coords(player_rect.right(), player_rect.top());
  Point player_bottom_coords(player_rect.right(), player_rect.bottom());
  Point player_delta_top(player_top_coords.x + delta, player_top_coords.y);
  Point player_delta_bottom(player_bottom_coords.x + delta, player_bottom_coords.y);

  if (player_collide_horizontal(player_delta_top, player_delta_bottom))
    return;

  player->move(delta, 0);
  check_and_move_camera();
}

void handle_input(sf::RenderWindow* window) {
  sf::Event event;
  while (window->pollEvent(event)) {
    if (event.type == sf::Event::KeyPressed) {
      switch(event.key.code) {
        case sf::Keyboard::Escape:
          window->close();
          break;
        case sf::Keyboard::Up:
          player_move_up(-MOVE_DELTA);
          break;
        case sf::Keyboard::Down:
          player_move_down(MOVE_DELTA);
          break;
        case sf::Keyboard::Right:
          player_move_right(MOVE_DELTA);
          break;
        case sf::Keyboard::Left:
          player_move_left(-MOVE_DELTA);
          break;
      }
    }

    if (event.type == sf::Event::Closed)
      window->close();
  }
}

void game_loop(sf::RenderWindow* window) {
  while (window->isOpen()) {
    //TODO: Implement a real View class/struct
    Point view;
    view.x = camera.x + WINDOW_WIDTH;
    view.y = camera.y + WINDOW_HEIGHT;

    handle_input(window);
    window->clear(sf::Color::Black);
    Point tile_start = toTileCoords(camera);

    Point draw_start = toTileCoords(camera);
    Point draw_end = toTileCoords(view);
    draw_start.x = draw_start.x < 0 ? 0 : draw_start.x;
    draw_start.y = draw_start.y < 0 ? 0 : draw_start.y;
    draw_start.x = draw_start.x > MAP_WIDTH ? MAP_WIDTH : draw_start.x;
    draw_start.y = draw_start.y > MAP_HEIGHT ? MAP_HEIGHT : draw_start.y;
    draw_end.x = draw_end.x > MAP_WIDTH ? MAP_WIDTH : draw_end.x;
    draw_end.y = draw_end.y > MAP_HEIGHT ? MAP_HEIGHT : draw_end.y;
    draw_end.x = draw_end.x < 0 ? 0 : draw_end.x;
    draw_end.y = draw_end.y < 0 ? 0 : draw_end.y;

    for (int i=draw_start.y-1; i < draw_end.y+1; ++i) {
      Point row_coords = fromTileCoords(0, i);
      if (i < 0 || i == MAP_WIDTH)
        continue;
      for (int j=draw_start.x-1; j < draw_end.x+1; ++j) {
        if (j < 0 || j == MAP_WIDTH)
          continue;
        game_map[j][i]->draw(window, Point(j * TILE_WIDTH - camera.x, i * TILE_HEIGHT - camera.y));
      }
    }
    player->draw(window, camera);
    window->display();
  }
}


int main(int argc, char ** argv)
{
  sf::RenderWindow* window = init_sfml();
  window->setVerticalSyncEnabled(true);
  init_game();
  init_map();
  game_loop(window);
  deinitialize_game(window);
  unload_map();
  return 0;
}
