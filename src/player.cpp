#include "player.h"

Player::Player(sf::Sprite* sprite) : _sprite(sprite){
  _position.x = 0;
  _position.y = 0;
}


Player::~Player() {
  std::cout << "Cleaning up player" << std::endl;
}

void Player::draw(sf::RenderWindow* window, Point camera)
{
    _sprite->setPosition(_position.x - camera.x, _position.y - camera.y);
    window->draw(*_sprite);
}

void Player::move(int x, int y) {
  _position.x += x;
  _position.y += y;
}

void Player::move(Point delta) {
  _position.x += delta.x;
  _position.y += delta.y;
}

Point Player::position() {
  return _position;
}
