#ifndef UTILITIES_H
#define UTILITIES_H

#include "imgui.h"
#include "imgui-SFML.h"

#include "view.hpp"

const inline unsigned int coords(const unsigned int x, const unsigned int y, const unsigned int sizeX){
  return x+y*sizeX;
}

// sf::Vector2i getTileCoords(const sf::RenderWindow &window, const viewPort &view){
//   sf::Vector2i pos=sf::Mouse::getPosition(window);

//   ImGui::InputInt("Mouse x", &pos.x);
//   ImGui::InputInt("Mouse y", &pos.y);
//   ImGui::Text("Mouse Tile position");

//   //Scale the position by the view's current zoom, so we know which pixel we're on
//   pos.x=pos.x*view.getScale();
//   pos.y=pos.y*view.getScale();
//   //The position of the pixel we're on should be of the world, not the window, so we add the view's position
//   pos.x+=view.getPos().x;
//   pos.y+=view.getPos().y;
//   //The center of the view is in the middle of the screen, while the cursor's is on the top-left corner, we adjust this here
//   pos.x-=(window.getSize().x*view.getScale())/2;
//   pos.y-=(window.getSize().y*view.getScale())/2;
//   //Divide the screen by the tile size, so we know which tile we're pointing to
//   pos.x=pos.x/32;
//   pos.y=pos.y/32;

//   ImGui::InputInt("Mouse tile x", &pos.x);
//   ImGui::InputInt("Mouse tile y", &pos.y);

//   return pos;
// }

#endif
