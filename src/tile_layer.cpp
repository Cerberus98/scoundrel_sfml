#include "tile_layer.h"

namespace Scoundrel {
  TileLayer::TileLayer(U32 width, U32 height) {
    _tile_width = width;
    _tile_height = height;
    _tile = NULL;
  }

  void TileLayer::draw(sf::RenderWindow* window, U32 x, U32 y) {
    if (_tile) {
      _tile->draw(window, x, y);
    }
  }

  void TileLayer::add_tile(Tile* tile) {
    _tile = tile;
  }
}
