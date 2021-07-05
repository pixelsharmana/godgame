#ifndef GRASS_H
#define GRASS_H

#include <SFML/Graphics.hpp>
#include <vector>

#include "OpenSimplexNoise.hpp"

class Grass{
private:
  const unsigned int textureSize=512;
  std::vector<uint8_t> vecgrass;
  sf::Texture textureGrass;
  double evaluation, level1, level2, level3, level4, level5, roughness;
  OpenSimplexNoise osn;
  int xoffset, yoffset, seed;

  void generate() {
	for(double i=xoffset; i < textureSize+xoffset; i++) {
	  for(double j=yoffset; j < yoffset+textureSize*4; j++) {
        level5 = osn.Evaluate(i/160, j/640);
        level4 = osn.Evaluate(i/80, j/320);
        level3 = osn.Evaluate(i/40, j/160);
        level2 = osn.Evaluate(i/20, j/80);
        level1 = osn.Evaluate(i/10, j /40);
        roughness = osn.Evaluate(i/2, j/8);
        evaluation = (level5/3 + level4/4 + level3/8 + level2/16 + level1/32)/12 + roughness/10;
        evaluation += 0.864366;
        evaluation /= 1.728732;
        if(evaluation > 1.0) { evaluation = 1.0; }
        else if(evaluation < 0.0) { evaluation = 0.0; }
        evaluation *= 255;
        vecgrass.push_back((uint8_t) evaluation);
      }
    }
    textureGrass.update(vecgrass.data());
  }

public:
  Grass(int x = 0, int y = 0, int s = 0) {
    textureGrass.create(textureSize, textureSize);
    xoffset = x;
    yoffset = y;
    seed = s;
    generate();
  }
  sf::Texture const getGrass() { return textureGrass; }
};

#endif
