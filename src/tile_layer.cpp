#include "tile_layer.h"

namespace Scoundrel {
  TileLayer::TileLayer(U32 width, U32 height) {
    _tile_width = width;
    _tile_height = height;
    _drawable = NULL;
  }

  void TileLayer::draw(sf::RenderWindow* window, U32 x, U32 y) {
    if (_drawable) {
      _drawable->setPosition(x, y);
      window->draw(*_drawable);
    }
  }

  void TileLayer::set_drawable(Drawable* drawable) {
    _drawable = drawable;
  }
}
