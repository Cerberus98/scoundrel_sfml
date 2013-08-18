#include <SFML/Window.hpp>

#include "scoundrel_utils.h"

class Entity {
public:
  Entity();
  virtual ~Entity();
  virtual Point position()=0;
  virtual void draw(sf::RenderWindow* window);

protected:
  Point _position;
};
