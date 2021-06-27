#ifndef VIEW_H
#define VIEW_H

#include <SFML/Graphics.hpp>

#include "imgui.h"
#include "imgui-SFML.h"

class viewPort{
private:
  sf::View view;
  double scale=1;
  double baseSpeed=0.1f;
  bool up=0, down=0, left=0, right=0;
public:
  //Takes a mouse event to zoom up or down and a keyboard event to move the view around
  //The speed of the movement is based on baseSpeed and scale, and scale gets changed by scrolling
  void move(const sf::Event&);
  //Updates the view position, should be called each frame, takes the active window as argument
  void update(sf::RenderWindow&);
  const double getScale() const;
  const sf::Vector2f getPos() const;
  viewPort(sf::RenderWindow&);
};

#endif
