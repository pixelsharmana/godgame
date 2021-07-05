#ifndef DIRT_H
#define DIRT_H

#include <SFML/Graphics.hpp>
#include <vector>

#include "OpenSimplexNoise.hpp"

class Dirt{
private:
  const unsigned int textureSize=512;
  std::vector<uint8_t> vecdirt;
  sf::Texture textureDirt;
  double evaluation2, level5, roughness;
  OpenSimplexNoise osn;
  int xoffset, yoffset, seed;

  void generate() {
	for(double i=xoffset; i < textureSize+xoffset; i++) {
	  for(double j=yoffset; j < yoffset+textureSize*4; j++) {
        level5 = osn.Evaluate(i/160, j/640);
        roughness = osn.Evaluate(i/2, j/8);
        evaluation2 = 0.55 + (level5/12 + roughness/12)/2;
        evaluation2 += 0.864366;
        evaluation2 /= 1.728732;
        if(evaluation2 > 1.0) { evaluation2 = 1.0; }
        else if(evaluation2 < 0.0) { evaluation2 = 0.0; }
        evaluation2 *= 255;
        vecdirt.push_back((uint8_t) evaluation2);
      }
    }
    textureDirt.update(vecdirt.data());
  }

public:
  Dirt(int x = 0, int y = 0, int s = 0) {
    textureDirt.create(textureSize, textureSize);
    xoffset = x;
    yoffset = y;
    seed = s;
    generate();
  }
  sf::Texture const getDirt() { return textureDirt; }
};

#endif
