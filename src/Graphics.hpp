#pragma once

#include <SFML/Graphics/BlendMode.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>

#include <string>

namespace cc{
  // we just init the sprite really
  struct Sprite{
    public:
    sf::Texture texture;
    sf::Sprite sprite; 
    sf::BlendMode blend;
    float angle;

    Sprite(std::string source, sf::Rect<int> size = sf::Rect<int>(-1,-1,0,0)){
      if(texture.loadFromFile(source)){
        // Did not specify size
        if(size!=sf::Rect<int>(-1,-1,0,0)){
          sprite.setTextureRect(size);
        } 
          sprite.setTexture(texture);
        // Center will be automatic choice
        sf::Rect<int> org = (sf::Rect<int>)sprite.getTextureRect();
        org.width  /= 2;
        org.height /= 2;
        sprite.setOrigin(org.width,org.height);
      }else{
        // Log error here
      }
    }

  };
}
