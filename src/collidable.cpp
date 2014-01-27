#include "collidable.h"

namespace Scoundrel {

  Collidable::Collidable() {}
  void Collidable::perform_collision_action(Player* player, int& current_level) {
    std::cout << "Base collide" << std::endl;  
  }
}
