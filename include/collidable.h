#ifndef SCOUNDREL_COLLIDABLE
#define SCOUNDREL_COLLIDABLE

#include <iostream>
#include "player.h"

class Collidable {
public:
  Collidable();
  virtual void perform_collision_action(Player* player, int& current_level);


};

#endif
