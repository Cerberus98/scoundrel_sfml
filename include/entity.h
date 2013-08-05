#include <SFML/Window.hpp>

class Entity {
  public:
  Entity();
  virtual ~Entity();
  virtual void draw(sf::RenderWindow* window)=0;

  int x, y;
};
