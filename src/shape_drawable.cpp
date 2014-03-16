#include "shape_drawable.h"

namespace Scoundrel {
  RectangleDrawable::RectangleDrawable(U32 width, U32 height, sf::Color color) {
    _width = width;
    _height = height;
    _color = color;
  }

  void RectangleDrawable::draw(sf::RenderTarget& target, sf::RenderStates states) const
  {
    sf::RectangleShape rect;
    states.transform *= getTransform();
    rect.setSize(sf::Vector2f(_width, _height));
    rect.setFillColor(_color);
    target.draw(rect, states);
  }
}
