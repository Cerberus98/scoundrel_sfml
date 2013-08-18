#include "tile.h"

Tile::Tile() {
}

Tile::Tile(sf::Sprite* sprite, int index_x, int index_y) {
  texture = sprite;
  index_x = index_x;
  index_y = index_y;
}

void Tile::draw(sf::RenderWindow* window, Point position) {
  texture->setPosition(position.x, position.y);
  window->draw(*texture);
}

bool Tile::passable() {
  return _passable;
}
