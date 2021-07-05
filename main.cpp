#include <iostream>
#include <vector>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Graphics.hpp>

#include "imgui.h"
#include "imgui-SFML.h"

#include "terrain.hpp"
#include "view.hpp"

#include "dirt.hpp"
#include "grass.hpp"


int main(){
  sf::Color background(30, 63, 98);
  sf::RenderWindow window(sf::VideoMode(1920, 1080), "Godgame");
  viewPort view(window);
  ImGui::SFML::Init(window);
  ImGuiIO& io=ImGui::GetIO();
  io.MouseDrawCursor=true;
  sf::Clock deltaClock;
  sf::Texture textureGrass, textureDirt;
  sf::Sprite spriteGrass, spriteDirt;
  std::vector<uint8_t> vecgrass, vecdirt;
  sf::Color dirt(130,84,15);

  Dirt durt;
  Grass grass;

  double evaluation1, evaluation2, level1, level2, level3, level4, level5, roughness;  
  
  spriteDirt.setColor(dirt);
  spriteGrass.setColor(sf::Color::Green);
  
  textureDirt = durt.getDirt();
  textureGrass = grass.getGrass();
  
  spriteDirt.setTexture(textureDirt);
  spriteGrass.setTexture(textureGrass);

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
	
	spriteGrass.setColor(grass);
	

	window.draw(spriteDirt);
	window.draw(spriteGrass);
	view.update(window);

	ImGui::End();
	ImGui::SFML::Render(window);
	window.display();
  }

  return 0;
}
