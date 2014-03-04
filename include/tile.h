#ifndef SCOUNDREL_TILE
#define SCOUNDREL_TILE

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

#include "drawable.h"
#include "scoundrel_utils.h"
#include "types.h"

namespace Scoundrel {
  class Tile {
    /* Represents an individual tile in a map */
  public:
    Tile();
    Tile(Drawable* drawable);
    void draw(sf::RenderWindow* window, U32 x, U32 y);
    void draw(sf::RenderWindow* window, Point position);
    void set_drawable(Drawable* drawable);
    Drawable * get_drawable();

  private:
    void _draw(sf::RenderWindow* window, U32 x, U32 y);
    Drawable* _drawable;
    //TODO: This needs a reference back to the array with pointer back to the array later
    //      See http://www.codeofhonor.com/blog/tough-times-on-the-road-to-starcraft for excellent reasons why
    int index_x, index_y; // reverse indices into the map
  };
}

#endif
