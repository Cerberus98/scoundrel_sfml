#ifndef SCOUNDREL_ASSET
#define SCOUNDREL_ASSET

#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>

namespace Scoundrel {
  class Asset {
  private:
    const char*     name;
    const char*     path;
    sf::Texture     texture;
    sf::Sprite      sprite;
    sf::Text        text;
    sf::Font        font;
    sf::Glyph       glyph;
    sf::Sound       sound;
    sf::SoundBuffer soundbuffer;
    sf::Music       music;
  public:
    Asset(std::string the_name, std::string the_path);
    inline const char* get_name() {return name;}
    inline const char* get_path() {return path;}
    void load_asset();
  };

}


#endif