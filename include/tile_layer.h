#include <iostream>

#include "layer.h"
#include "tile.h"
#include "types.h"

#ifndef SCOUNDREL_TILE_LAYER
#define SCOUNDREL_TILE_LAYER

namespace Scoundrel {
  class TileLayer : public Layer {
  public:
    TileLayer(U32 tile_width, U32 tile_height);
    void draw(sf::RenderWindow* window, U32 x, U32 y);

    //TODO This goes away, need to think about this interface
    void add_tile(Tile* tile);

  private:
    U32 _tile_width, _tile_height;

    //TODO Remove this when you fix set_drawable above
    Tile* _tile;

  };
}


#endif
