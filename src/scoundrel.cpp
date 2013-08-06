#include <iostream>

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

#include "player.h"


const int MAP_WIDTH = 100, MAP_HEIGHT = 100;
const int WINDOW_WIDTH = 800, WINDOW_HEIGHT = 600;
const int TILE_WIDTH = 32, TILE_HEIGHT = 32;
int** game_map;
sf::Sprite* tiles;
sf::Texture* textures;

struct Point {
  int x, y;
};

Point camera;

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
  game_map = new int*[MAP_WIDTH];
  for (int i=0; i <MAP_WIDTH; ++i) {
    game_map[i] = new int[MAP_HEIGHT];
    for (int j=0; j < MAP_HEIGHT; j++) {
      game_map[i][j] = rand() % 2;
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
  tiles = new sf::Sprite[5];
  textures = new sf::Texture[5];
  textures[0] = load_image("grass_32.jpg");
  tiles[0].setTexture(textures[0]);

  textures[1] = load_image("dirt_32.png");
  tiles[1].setTexture(textures[1]);
}

void deinitialize_game(sf::RenderWindow* window) {
  delete window;
  delete[] textures;
  delete[] tiles;
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
          camera.y -= 4;
          break;
        case sf::Keyboard::Down:
          camera.y += 4;
          break;
        case sf::Keyboard::Right:
          camera.x += 4;
          break;
        case sf::Keyboard::Left:
          camera.x -= 4;
          break;
      }
    }
    if (event.type == sf::Event::Closed)
      window->close();
  }
}

void game_loop(sf::RenderWindow* window) {
  Player player;
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
        Point tile_world_coords = fromTileCoords(j, i);

        sf::Sprite tile = tiles[game_map[j][i]];
        tile.setPosition(j * TILE_WIDTH - camera.x, i * TILE_HEIGHT - camera.y);
        window->draw(tile);
      }
    }

    window->display();
  }
}


int main(int argc, char ** argv)
{
  init_map();
  sf::RenderWindow* window = init_sfml();
  window->setVerticalSyncEnabled(true);
  init_game();
  game_loop(window);
  deinitialize_game(window);
  unload_map();
  return 0;
}
