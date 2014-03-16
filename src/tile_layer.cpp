#include "tile_layer.h"

namespace Scoundrel {
  TileLayer::TileLayer(U32 tile_width, U32 tile_height) {
    _tile_width = tile_width;
    _tile_height = tile_height;
    _map = NULL;
  }

  void TileLayer::draw(sf::RenderWindow* window, Camera* camera) {
    if (_map) {
      Point camera_pos = camera->position();
      TileHelper tile_helper(_tile_width, _tile_height);
      Rectangle view = camera->get_view_rect();
      Point draw_start = tile_helper.toTileCoords(view.left() - 32, view.top() - 32);
      Point draw_end = tile_helper.toTileCoords(view.right() + 32, view.bottom() + 32);

      // Some basic attempts at tile clipping
      draw_start.x = draw_start.x < 0 ? 0 : draw_start.x;
      draw_start.y = draw_start.y < 0 ? 0 : draw_start.y;
      draw_start.x = draw_start.x > _map_width ? _map_width : draw_start.x;
      draw_start.y = draw_start.y > _map_height ? _map_height : draw_start.y;

      draw_end.x = draw_end.x > _map_width ? _map_width : draw_end.x;
      draw_end.y = draw_end.y > _map_height ? _map_height : draw_end.y;
      draw_end.x = draw_end.x < 0 ? 0 : draw_end.x;
      draw_end.y = draw_end.y < 0 ? 0 : draw_end.y;

      for (I32 i = draw_start.y - 1; i < draw_end.y + 1; ++i) {
        if (i < 0 || i == _map_height)
          continue;
        for (I32 j = draw_start.x - 1; j < draw_end.x + 1; ++j) {
          if (j < 0 || j == _map_width)
            continue;

          _map[i][j]->draw(window, j * _tile_width - camera_pos.x, i * _tile_height - camera_pos.y);
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
