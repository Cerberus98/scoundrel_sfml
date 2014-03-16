#include <iostream>

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

#include "drawable.h"
#include "types.h"

#ifndef SCOUNDREL_SHAPE_DRAWABLE
#define SCOUNDREL_SHAPE_DRAWABLE

namespace Scoundrel {
  class ShapeDrawable : public Drawable {
  public:
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const = 0;
  };

  class RectangleDrawable : public ShapeDrawable {
  public:
    RectangleDrawable(U32 width, U32 height, sf::Color color);
    void draw(sf::RenderTarget& target, sf::RenderStates states) const;
  
  private:
    U32 _width, _height;
    sf::Color _color;

  };
}


#endif
