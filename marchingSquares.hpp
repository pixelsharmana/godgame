#ifndef MARCHING_H
#define MARCHING_H

#include <SFML/Graphics.hpp>
#include <vector>

#include "imgui.h"
#include "imgui-SFML.h"

#include "noise.hpp"
#include "utilities.hpp"

class marching : public sf::Drawable{
private:
  unsigned int height;
  unsigned int width;
  unsigned int gap=20;
  std::vector<uint8_t> values;

  unsigned int getState(unsigned int x, unsigned int y) const {
	unsigned int output=0;
	output+=values.at(coords(x,   y,     width)) * 1;
	output+=values.at(coords(x+1, y,     width)) * 2;
	output+=values.at(coords(x+1, y+1,   width)) * 4;
	output+=values.at(coords(x,   y+1,   width)) * 8;
	return output;
  }

  void drawIsoLines(sf::RenderTarget& target) const {
	for(unsigned int x=0;x<height-1;x++){
	  for(unsigned int y=0;y<width-1;y++){
		short isoState=getState(x, y);
		if(isoState==1 || isoState==14){
		  sf::Vertex line[]={
			sf::Vertex(sf::Vector2f(x*gap+(gap/2), y*gap)),
			sf::Vertex(sf::Vector2f(x*gap, y*gap+(gap/2)))};
		  target.draw(line, 2, sf::Lines);
		}else if(isoState==2 || isoState==13){
		  sf::Vertex line[]={
			sf::Vertex(sf::Vector2f(x*gap+(gap/2), y*gap)),
			sf::Vertex(sf::Vector2f((x+1)*gap, y*gap+(gap/2)))};
		  target.draw(line, 2, sf::Lines);
		}else if(isoState==3 || isoState==12){
		  sf::Vertex line[]={
			sf::Vertex(sf::Vector2f(x*gap, y*gap+(gap/2))),
			sf::Vertex(sf::Vector2f((x+1)*gap, y*gap+(gap/2)))};
		  target.draw(line, 2, sf::Lines);
		}else if(isoState==4 || isoState==11){
		  sf::Vertex line[]={
			sf::Vertex(sf::Vector2f(x*gap+(gap/2), (y+1)*gap)),
			sf::Vertex(sf::Vector2f((x+1)*gap, y*gap+(gap/2)))};
		  target.draw(line, 2, sf::Lines);
		}else if(isoState==5 || isoState==10){
		  sf::Vertex line[]={
			sf::Vertex(sf::Vector2f(x*gap+(gap/2), y*gap)),
			sf::Vertex(sf::Vector2f((x+1)*gap, y*gap+(gap/2)))};
		  target.draw(line, 2, sf::Lines);
		  sf::Vertex line2[]={
			sf::Vertex(sf::Vector2f(x*gap, y*gap+(gap/2))),
			sf::Vertex(sf::Vector2f(x*gap+(gap/2), (y+1)*gap))};
		  target.draw(line2, 2, sf::Lines);
		}else if(isoState==6 || isoState==9){
		  sf::Vertex line[]={
			sf::Vertex(sf::Vector2f(x*gap+(gap/2), y*gap)),
			sf::Vertex(sf::Vector2f(x*gap+(gap/2), (y+1)*gap))};
		  target.draw(line, 2, sf::Lines);
		}else if(isoState==7 || isoState==8){
		  sf::Vertex line[]={
			sf::Vertex(sf::Vector2f(x*gap, y*gap+(gap/2))),
			sf::Vertex(sf::Vector2f(x*gap+(gap/2), (y+1)*gap))};
		  target.draw(line, 2, sf::Lines);
		}
	  }
	}
  }

public:
  void draw(sf::RenderTarget& target, sf::RenderStates states) const {
	static bool valueflag=1;
	ImGui::Checkbox("Render values", &valueflag);
	if(valueflag){
	  for(unsigned int x=0;x<height;x++){
		for(unsigned int y=0;y<width;y++){
		  sf::CircleShape c;
		  c.setRadius(1);
		  uint8_t color=values.at(coords(x, y, width))*255;
		  c.setFillColor({color, color, color, 126});
		  c.setPosition(x*gap, y*gap);
		  target.draw(c);
		}
	  }
	}

	static bool linesflag=1;
	ImGui::Checkbox("Render isolines", &linesflag);
	if(linesflag){
	  drawIsoLines(target);
	}
  }

  marching(unsigned int h, unsigned int w, unsigned int seed=1337){
	height=h;
	width=w;
	values.reserve(h*w);
	for(unsigned int x=0;x<h;x++){
	  for(unsigned int y=0;y<w;y++){
		double temp=normalise(noise2d(x, y, seed));
		if(temp>0.5){
		  values.push_back(1);
		}else{
		  values.push_back(0);
		}
	  }
	}
  }
};

#endif
