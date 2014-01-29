#ifndef SCOUNDREL_TILE
#define SCOUNDREL_TILE

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

#include "animation.h"
#include "scoundrel_utils.h"

namespace Scoundrel {
  class Tile {
    /* Represents an individual tile in a map */
  public:
    Tile(bool passable=true, bool deadly=false);
    Tile(Animation* animation, bool passable=true, bool deadly=false);
    void draw(sf::RenderWindow* window, Point position, float brightness);
    void set_animation(Animation* animation);
    Animation * get_animation();
    void set_passable(bool state);
    bool is_deadly();
    bool passable();

  private:
    Animation* _animation;
    bool _passable;
    bool _is_deadly;
    //TODO: This needs a reference back to the array with pointer back to the array later
    //      See http://www.codeofhonor.com/blog/tough-times-on-the-road-to-starcraft for excellent reasons why

    int index_x, index_y; // reverse indices into the map
  };
}

#endif
