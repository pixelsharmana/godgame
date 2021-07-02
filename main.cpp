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
  sf::Texture texturegrass, texturedirt;
  sf::Sprite spritegrass, spritedirt;
  std::vector<uint8_t> vecgrass, vecdirt;
  sf::Color dirt(130,84,15);

  double evaluation1, evaluation2, level1, level2, level3, level4, level5, roughness;  
  OpenSimplexNoise osn(1);
  
  
  spritedirt.setColor(dirt);
  
  texturegrass.create(1000, 1000);
  
  texturedirt.create(1000,1000);
  
  for(double i=0; i < 1000; i++) {
  	for(double j=0; j < 1000*4; j++) {
	  	
	  	level5 = osn.Evaluate(i/160, j/640);
	  	
	  	level4 = osn.Evaluate(i/80, j/320);
	  	
	  	level3 = osn.Evaluate(i/40, j/160);
	  	
	  	level2 = osn.Evaluate(i/20, j/80);
	  	
	  	level1 = osn.Evaluate(i/10, j/40);
	
		roughness = osn.Evaluate(i/2, j/8);

	  	//Uncomment this for grass
	  	evaluation1 = (level5/3 + level4/4 + level3/8 + level2/16 + level1/32)/12 + roughness/10;
	  	
	  	evaluation2 = 0.68 + (level5/12 + roughness/12)/3;
	  	
	  	evaluation1 += 0.864366;
	  	
	  	evaluation1 /= 1.728732;
	  	
	  	evaluation2 += 0.864366;
	  	
	  	evaluation2 /= 1.728732;
	  	
	  	if(evaluation1 > 1.0) evaluation1 = 1.0;
	  	
	  	else if(evaluation1 < 0.0) evaluation1 = 0.0;
	  	
	  	if(evaluation2 > 1.0) evaluation2 = 1.0;
	  	
	  	else if(evaluation2 < 0.0) evaluation2 = 0.0;
	  	
	  	evaluation1 *= 255;
	  	
	  	evaluation2 *= 255;
	  	
		vecgrass.push_back((uint8_t) evaluation1);
		
		vecdirt.push_back((uint8_t) evaluation2);
	
	}
  }

  texturegrass.update(vecgrass.data());
  
  texturedirt.update(vecdirt.data());
  
  spritegrass.setTexture(texturegrass);
  
  spritedirt.setTexture(texturedirt);

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

	static int density;

	window.clear(background);
	ImGui::Begin("Debug menu");

	ImGui::SliderInt("Grass Density", &density, 0, 255);

	//Draw stuff
	
	sf::Color grass(0,255,0,(int)density);
	
	spritegrass.setColor(grass);
	

	window.draw(spritedirt);
	window.draw(spritegrass);
	view.update(window);

	ImGui::End();
	ImGui::SFML::Render(window);
	window.display();
  }

  return 0;
}
