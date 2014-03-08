#include "tile_layer.h"

namespace Scoundrel {
  TileLayer::TileLayer(U32 width, U32 height) {
    _tile_width = width;
    _tile_height = height;
    _map = NULL;
  }

  void TileLayer::draw(sf::RenderWindow* window, U32 x, U32 y) {
    //if (_map) {
    //  _map[0][0]->draw(window, x, y);
    //}
  }

  void TileLayer::attach_map(Tile*** tile) {
    _map = tile;
  }
}
