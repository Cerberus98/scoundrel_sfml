#include <iostream>

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "entity.h"

Entity::Entity():x(0), y(0) {
  std::cout << "Entity Constructor" << std::endl;
}

Entity::~Entity() {
  std::cout << "Deleting Entity" << std::endl;

}
