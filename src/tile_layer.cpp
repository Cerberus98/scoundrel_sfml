#include "tile_layer.h"

namespace Scoundrel {
  TileLayer::TileLayer(U32 tile_width, U32 tile_height) {
    _tile_width = tile_width;
    _tile_height = tile_height;
    _map = NULL;
  }

  void TileLayer::draw(sf::RenderWindow* window, Camera* camera) {
    Point pos = camera->position();
    U32 x = pos.x;
    U32 y = pos.y;

    if (_map) {
      for (int i = 0; i < _map_height; ++i) {
        for (int j = 0; j < _map_width; ++j) {
          U32 tile_x = j * _tile_width;
          U32 tile_y = i * _tile_height;
          _map[i][j]->draw(window, tile_x, tile_y);
        }
      }
    }
  }

  //TODO This likely changes to accept a type "TileMap" which itself
  //     is a 1D array of Tile pointers. The triple pointer thing
  //     is just too easy to typo in weird ways
  void TileLayer::attach_map(Tile*** tile, U32 width, U32 height) {
    _map = tile;
    _map_width = width;
    _map_height = height;
  }
}
