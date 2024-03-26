#pragma once

#include "Graphics.hpp"
#include <SFML/System/Vector2.hpp>
#include <boost/uuid/uuid.hpp>
#include <functional>

namespace cc{
   class GameObject{
    public:
    boost::uuids::uuid UUID;
    sf::Vector2<float> Position;
    cc::Sprite* Sprite;
    bool Enabled = true;

    // Constructor
    GameObject(std::string spritesource){
      Sprite = new cc::Sprite(spritesource);
    }

    // Events
    // TODO add cc::Game* to all here. resolve header issue. 
    std::function<void()> onCreate = []() {};
    std::function<void()> onEnabled = []() {};
    std::function<void(float deltaTimeMs)> onUpdate = [](float) {};
    std::function<void()> onFixedUpdate = []() {};
    std::function<void()> onGUI = []() {};
    std::function<void()> onDestroy = []() {};
  };
}
