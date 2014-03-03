#include <iostream>
#include "asset.h"

namespace Scoundrel {
  Asset::Asset(std::string the_name, std::string the_path, int the_type) {
    name = the_name.c_str();
    path = the_path.c_str();
    type = the_type;
    std::cout << "Initialized asset: " << the_name << "@" << the_path << std::endl;
  }
  
  void Asset::load_asset() {
    std::cout << "Loading asset: " << name << std::endl;
    switch (type) {
      case TEXTURE:
        if (!texture.loadFromFile(path)) {
          // error...
        }
        break;
      case SPRITE:
        if (!texture.loadFromFile(path)) {
          // error...
        } else {
          sprite.setTexture(texture);
        }
        break;
      default:
        break;
        
    }
    
  }
}