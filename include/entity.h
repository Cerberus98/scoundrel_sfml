#include <SFML/Window.hpp>

#include "scoundrel_utils.h"

class Entity {
  public:
  Entity();
  virtual ~Entity();
  virtual void draw(sf::RenderWindow* window, Point camera)=0;
};
