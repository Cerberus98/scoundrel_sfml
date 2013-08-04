#include <iostream>

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

const int MAP_WIDTH = 100, MAP_HEIGHT = 100;
const int WINDOW_WIDTH = 800, WINDOW_HEIGHT = 600;
const int TILE_WIDTH = 32, TILE_HEIGHT = 32;
int** game_map;
sf::Sprite* tiles;
sf::Texture* textures;

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
      game_map[i][j] = 1;
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
      std::cout << game_map[j] << " ";
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
}

void deinitialize_game(sf::RenderWindow* window) {
  delete window;
  delete[] textures;
  delete[] tiles;
}

void game_loop(sf::RenderWindow* window) {
  while (window->isOpen()) {
    sf::Event event;
    while (window->pollEvent(event)) {
      if (event.type == sf::Event::Closed)
        window->close();
    }
    window->clear(sf::Color::Green);
    for (int i=0; i < MAP_HEIGHT; ++i) {
      for (int j=0; j < MAP_WIDTH; ++j) {
        sf::Sprite tile = tiles[0];
        tile.setPosition(j * TILE_WIDTH, i * TILE_HEIGHT);
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
  init_game();
  game_loop(window);
  deinitialize_game(window);
  unload_map();
  return 0;
}
