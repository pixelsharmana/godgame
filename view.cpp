#include "view.hpp"

#include <iostream>

void viewPort::move(const sf::Event &event){
  //Handling the zoom
  if(event.type == sf::Event::MouseWheelScrolled){
	if (event.mouseWheelScroll.wheel == sf::Mouse::VerticalWheel){
	  if(event.mouseWheelScroll.delta<0){
		scale*=1.1;
		view.zoom(1.1);
	  }else{
		scale*=1/1.1;
		view.zoom(1/1.1);
	  }
	}
  }

  //Keyboard
  if (event.type == sf::Event::KeyPressed){
	if((event.key.code == sf::Keyboard::W) || (event.key.code == sf::Keyboard::Up)){
	  up=true;
	}else if((event.key.code == sf::Keyboard::S) || (event.key.code == sf::Keyboard::Down)){
	  down=true;
	}else if((event.key.code == sf::Keyboard::A) || (event.key.code == sf::Keyboard::Left)){
	  left=true;
	}else if((event.key.code == sf::Keyboard::D) || (event.key.code == sf::Keyboard::Right)){
	  right=true;
	}
  }else if (event.type == sf::Event::KeyReleased){
	if((event.key.code == sf::Keyboard::W) || (event.key.code == sf::Keyboard::Up)){
	  up=false;
	}else if((event.key.code == sf::Keyboard::S) || (event.key.code == sf::Keyboard::Down)){
	  down=false;
	}else if((event.key.code == sf::Keyboard::A) || (event.key.code == sf::Keyboard::Left)){
	  left=false;
	}else if((event.key.code == sf::Keyboard::D) || (event.key.code == sf::Keyboard::Right)){
	  right=false;
	}
  }
}

void viewPort::update(sf::RenderWindow& window){
  if(up){
	view.move(0.f, -baseSpeed*scale);
  }if(down){
	view.move(0.f, baseSpeed*scale);
	}if(left){
	view.move(-baseSpeed*scale, 0.f);
  }if(right){
	view.move(baseSpeed*scale, 0.f);
  }

  if(ImGui::CollapsingHeader("Camera")){
	ImGui::InputDouble("Camera zoom", &scale, 0.01f, 1.0f, "%.2f");
	ImGui::InputDouble("Base camera speed", &baseSpeed, 0.01f, 1.0f, "%.2f");
	auto pos=view.getCenter();
	ImGui::InputFloat("Camera x", &pos.x, 0.01f, 1.0f, "%.2f");
	ImGui::InputFloat("Camera y", &pos.y, 0.01f, 1.0f, "%.2f");
  }

  window.setView(this->view);
}

const double viewPort::getScale() const{
  return scale;
}

const sf::Vector2f viewPort::getPos() const{
  return view.getCenter();
}

viewPort::viewPort(sf::RenderWindow& window){
  view.setSize(window.getSize().x, window.getSize().y);
  view.setCenter(0, 0);
  window.setView(this->view);
}
