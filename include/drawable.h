#include <SFML/Graphics.hpp>

#ifndef SCOUNDREL_DRAWABLE
#define SCOUNDREL_DRAWABLE

namespace Scoundrel {
  //TODO: This consolidates the two inane subclasses we need to use otherwise. 
  //      Convert this to a coherent interface that provides several ways of drawing,
  //      either by relying on the transformable or by passing a rect, point, int coords etc.
  class Drawable : public sf::Drawable, public sf::Transformable {
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const = 0;
  };
}

#endif
