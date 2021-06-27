#include <iostream>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Graphics.hpp>

#include "imgui.h"
#include "imgui-SFML.h"

#include "terrain.hpp"
#include "view.hpp"

int main(){
  sf::Color background(30, 63, 98);
  sf::RenderWindow window(sf::VideoMode(1920, 1080), "Godgame");
  viewPort view(window);
  ImGui::SFML::Init(window);
  ImGuiIO& io=ImGui::GetIO();
  io.MouseDrawCursor=true;
  sf::Clock deltaClock;

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

	window.draw(myTerrain);
	view.update(window);

	ImGui::End();
	ImGui::SFML::Render(window);
	window.display();
  }

  return 0;
}
