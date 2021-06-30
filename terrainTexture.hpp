#include <iostream>

#include <SFML/Graphics.hpp>

#include "imgui.h"
#include "imgui-SFML.h"

#include "noise.hpp"

Class terrainTexture {
	
	sf::Texture terrainTexture(int x=0, int y=0, int seed=0) {
		sf::Texture texture;
		std::vector<uint8_t> vec;
		
		for(int i=0; i < x*y*4; i++)
			vec.push_back(noise(i, seed));


		return vec.data();
	}	

}
