#include "terrain.hpp"

void terrain::draw(sf::RenderTarget& target, sf::RenderStates states) const {
  static bool show=true;
  ImGui::Checkbox("Render terrain", &show);
  if(show){
	unsigned int offsetX=0, offsetY=0, count=0;
	for(const auto &i:map){
	  sf::Sprite current=textureAtlas.get(i);
	  current.setPosition(offsetX*32, offsetY*32);
	  count++;
	  offsetX++;
	  if(count==width){
		count=0;
		offsetX=0;
		offsetY++;
	  }
	  target.draw(current);
	}
  }
}

tileType terrain::get(unsigned int x, unsigned int y) const {

}

void terrain::set(unsigned int x, unsigned int y, const tileType input){

}

terrain::terrain(unsigned int inputHeight, unsigned int inputWidth):height(inputHeight),width(inputWidth){
  map.resize(height*width);
  for(auto &i:map){
	i=tileType::plain;
  }
}
