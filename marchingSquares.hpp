#ifndef MARCHING_H
#define MARCHING_H

#include <SFML/Graphics.hpp>
#include <vector>

#include "imgui.h"
#include "imgui-SFML.h"

#include "noise.hpp"
#include "utilities.hpp"

class marching : public sf::Drawable{
public:
  unsigned int height;
  unsigned int width;
  unsigned int gap=40;
  std::vector<sf::CircleShape> circles;

  void draw(sf::RenderTarget& target, sf::RenderStates states) const {
	for(auto &i:circles){
	  target.draw(i);
	}
  }

  marching(unsigned int h, unsigned int w, unsigned int seed=1337){
	height=h;
	width=w;
	circles.reserve(h*w);
	for(unsigned int x=0;x<h;x++){
	  for(unsigned int y=0;y<w;y++){
		sf::CircleShape c;
		c.setRadius(15);
		c.setPosition(x*gap, y*gap);
		double color=normalise(noise2d(x, y, seed));
		if(color>0.5){
		  color=255;
		}else{
		  color=0;
		}
		c.setFillColor({static_cast<uint8_t>(color), static_cast<uint8_t>(color), static_cast<uint8_t>(color)});
		circles.push_back(c);
	  }
	}
  }
};

#endif
