#include <iostream>

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

#include "entity.h"

class Player : public Entity {

public:
  ~Player();
  void draw(sf::RenderWindow * window);
};
