#include "tile.hpp"

sf::Sprite atlas::get(const tileType input) const{
  sf::Sprite sprite;
  sprite.setTexture(atlasTexture);
  sprite.setTextureRect(sf::IntRect(sub.at(input).x, sub.at(input).y, textureSize, textureSize));
  return sprite;
}

atlas::atlas(){
  if(!atlasTexture.loadFromFile("tiles/atlas.png")){
	std::cerr << "Couldn't load atlas texture";
  }
  sub.insert({tileType::plain,  {0,           0}});
  sub.insert({tileType::forest, {textureSize, 0}});
  sub.insert({tileType::sand,   {0,           textureSize}});
  sub.insert({tileType::ocean,  {textureSize, textureSize}});
}
