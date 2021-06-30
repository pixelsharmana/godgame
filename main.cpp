#include <iostream>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Graphics.hpp>

#include "imgui.h"
#include "imgui-SFML.h"

#include "terrain.hpp"
#include "view.hpp"

#include "OpenSimplexNoise.hpp"

int main(){
  sf::Color background(30, 63, 98);
  sf::RenderWindow window(sf::VideoMode(1920, 1080), "Godgame");
  viewPort view(window);
  ImGui::SFML::Init(window);
  ImGuiIO& io=ImGui::GetIO();
  io.MouseDrawCursor=true;
  sf::Clock deltaClock;
  sf::Texture texture;
  sf::Sprite sprite;
  std::vector<uint8_t> vec;
  double evaluation, level1, level2, level3, level4, level5, base1, base2;  
  OpenSimplexNoise osn(1);
  
  sprite.setColor(sf::Color::Green);
  
  texture.create(1000, 1000);
  
  for(double i=0; i < 1000; i++) {
  	for(double j=0; j < 1000*4; j++) {
	  	
	  	level5 = osn.Evaluate(i/160, j/640);
	  	
	  	level4 = osn.Evaluate(i/80, j/320);
	  	
	  	level3 = osn.Evaluate(i/40, j/160);
	  	
	  	level2 = osn.Evaluate(i/20, j/80);
	  	
	  	level1 = osn.Evaluate(i/10, j/40);
	
	  	//evaluation = 0.22;
	  	
	  	//evaluation = level1;
	  	
	  	//evaluation = level2;
	  	
	  	//evaluation = level3;
	  	
	  	//evaluation = level4;
	  	
	  	//evaluation = level5;
	  	
	  	evaluation = (level5/3 + level4/4 + level3/8 + level2/16 + level1/32)/4 + 0.45;
	  	
	  	evaluation += 0.864366;
	  	
	  	evaluation /= 1.728732;
	  	
	  	evaluation -=0.15;
	  	
	  	if(evaluation > 1.0) evaluation = 1.0;
	  	
	  	else if(evaluation < 0.0) evaluation = 0.0;
	  	
	  	evaluation *= 255;
	  	
		vec.push_back((uint8_t) evaluation);
	
	}
  }

  texture.update(vec.data());
  
  sprite.setTexture(texture);

  sprite.scale(1.0, 1.0);

  terrain myTerrain(9, 9);

  while (window.isOpen()){
	sf::Event event;
	while (window.pollEvent(event)){
	  ImGui::SFML::ProcessEvent(event);
	  view.move(event);
	  if (event.type == sf::Event::Closed)
		window.close();
	}
	ImGui::SFML::Update(window, deltaClock.restart());

	window.clear(background);
	ImGui::Begin("Debug menu");

	//Draw stuff

	window.draw(sprite);
	view.update(window);

	ImGui::End();
	ImGui::SFML::Render(window);
	window.display();
  }

  return 0;
}
