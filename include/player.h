#include <iostream>

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

#include "entity.h"
#include "scoundrel_utils.h"

#ifndef SCOUNDREL_PLAYER
#define SCOUNDREL_PLAYER

class Player : public Entity {

public:
  ~Player();
  Player(sf::Sprite * sprite);
  void draw(sf::RenderWindow * window, Point camera);
  void move(int x, int y);
  void move(Point delta);
  Point position();

private:
  sf::Sprite* _sprite;
};

#endif
