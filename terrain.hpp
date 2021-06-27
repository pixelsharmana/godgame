#ifndef TERRAIN_H
#define TERRAIN_H

#include <vector>

#include "imgui.h"
#include "imgui-SFML.h"

#include "view.hpp"
#include "tile.hpp"
#include "utilities.hpp"

class terrain : public sf::Drawable{
private:
  unsigned int height, width;
  std::vector<tileType> map;
  atlas textureAtlas;
  //std::map<tileType, sf::Sprite>;

public:
  tileType get(unsigned int x, unsigned int y) const;
  void set(unsigned int, unsigned int, const tileType);
  void draw(sf::RenderTarget& target, sf::RenderStates) const;
  terrain(unsigned int, unsigned int);
};

void terrainEdit(const sf::Vector2i, const tileType);

#endif
