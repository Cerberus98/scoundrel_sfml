#include <iostream>

#include "camera.h"
#include "layer.h"

//TODO: This is a terrible place for Point to live
#include "scoundrel_utils.h"
#include "tile.h"
#include "tile_helper.h"
#include "types.h"

#ifndef SCOUNDREL_TILE_LAYER
#define SCOUNDREL_TILE_LAYER

namespace Scoundrel {
  class TileLayer : public Layer {
  public:
    TileLayer(U32 tile_width, U32 tile_height);
    void draw(sf::RenderWindow* window, Camera* camera);

    //TODO This goes away, need to think about this interface
    void attach_map(Tile*** map, U32 width, U32 height);

  private:
    U32 _tile_width, _tile_height;

    //TODO Remove this when you fix set_drawable above
    Tile*** _map;
    U32 _map_width, _map_height;

  };
}


#endif
