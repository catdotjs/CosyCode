#pragma once

#include "Graphics.hpp"
#include <SFML/System/Vector2.hpp>

namespace cc{
   class GameObject{
    public:
    int UID;
    sf::Vector2<float> Position;
    cc::Sprite* Sprite;
    bool Enabled = true;

    // Constructor
    GameObject(std::string spritesource){
      Sprite = new cc::Sprite(spritesource);
    }
    private:
    // Events
    void onCreate();
    void onEnabled();
    void onUpdate();
    void onFixedUpdate();
    void onGUI();
    void onDestroy();
  };
}
