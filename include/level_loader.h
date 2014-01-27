#ifndef SCOUNDREL_LEVEL_LOADER
#define SCOUNDREL_LEVEL_LOADER

#include <list>
#include <map>
#include <string>
#include <sstream>
#include <fstream>

#include <SFML/Audio.hpp>

#include "animation.h"
#include "camera.h"
#include "player.h"
#include "tile.h"
#include "tile_helper.h"

namespace Scoundrel {
  Tile*** load_map(std::string level_path, Player* player, Camera* camera, std::map<int, Scoundrel::Animation>* animation_map,
                          sf::Sound* sounds, std::list<Entity *>& game_entities, TileHelper* tile_helper, int& map_width,
                          int& map_height, int& ambient_light);
  Tile*** load_map(std::string level_path);
}

#endif
