#include "player.h"

Player::~Player() {
  std::cout << "Cleaning up player" << std::endl;
}

void Player::draw(sf::RenderWindow* window)
{
  std::cout << "Player::draw" << std::endl;
}
