#ifndef TILE_H
#define TILE_H

#include <SFML/Graphics.hpp>
#include <map>
#include <iostream>

enum class tileType{plain, forest, sand, ocean};

class atlas{
private:
  unsigned int textureSize=32;
  sf::Texture atlasTexture;
  std::map<tileType, sf::Vector2u> sub;
public:
  //Give it a tile type, get back a sprite
  sf::Sprite get(const tileType) const;
  atlas();
};

#endif
