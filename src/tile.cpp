#include "tile.h"

namespace Scoundrel {
  Tile::Tile() {
    _drawable = NULL;
  }

  Tile::Tile(Drawable* drawable) {
    _drawable = drawable;
  }

  void Tile::set_drawable(Drawable* drawable) {
    _drawable = drawable;
  }

  Drawable* Tile::get_drawable() {
    return _drawable;
  }

  void Tile::draw(sf::RenderWindow* window, I32 x, I32 y) {
    if (_drawable) {
      _drawable->setPosition(x, y);
      window->draw(*_drawable);
    }
  }

  void Tile::draw(sf::RenderWindow* window, Point position) {
    draw(window, position.x, position.y);
  }
}
