#ifndef SCOUNDREL_ANIMATION
#define SCOUNDREL_ANIMATION

// Inspired by https://github.com/LaurentGomila/SFML/wiki/Source%3A-AnimatedSprite

#include <vector>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/PrimitiveType.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Transformable.hpp>
#include <SFML/Graphics/Vertex.hpp>

class Animation : public sf::Drawable, public sf::Transformable
{
public:
  Animation();
  void add_frame(sf::IntRect rect);
  void set_sprite_sheet(sf::Texture* texture);
  int get_frame();
  void set_frame(int frame);

private:
  int _current_frame;
  sf::Vertex _vertices[4];
  std::vector<sf::IntRect> _frames;
  const sf::Texture* _texture;
  virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};

#endif
