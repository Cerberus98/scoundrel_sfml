#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "types.h"

#ifndef SCOUNDREL_LAYER
#define SCOUNDREL_LAYER

namespace Scoundrel {
  class Layer {
  public:
    virtual void draw(sf::RenderWindow* window, U32 x, U32 y) = 0;

  };
}


#endif
