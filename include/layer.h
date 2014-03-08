#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

#include "camera.h"
#include "types.h"

#ifndef SCOUNDREL_LAYER
#define SCOUNDREL_LAYER

namespace Scoundrel {
  class Layer {
  public:
    virtual void draw(sf::RenderWindow* window, Camera* camera) = 0;

  };
}


#endif
