#include <iostream>
#include "asset.h"

namespace Scoundrel {
  Asset::Asset(std::string the_name, std::string the_path) {
    name = the_name.c_str();
    path = the_path.c_str();
    std::cout << "Initialized asset: " << the_name << "@" << the_path << std::endl;
  }
  
  void Asset::load_asset() {
    std::cout << "Loading asset: " << name << std::endl;
    if (!texture.loadFromFile(path)) {
      // error...
      std::cout << "Could not load " << path << " (check the path)." << std::endl;
    } else {
      sprite.setTexture(texture);
      std::cout << "\tAsset loaded!" << std::endl;
    }
  }
}