#include "Graphics.hpp"
#include <SFML/System/Vector2.hpp>
#include <boost/uuid/uuid.hpp>

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
    void onCreate(){};
    void onEnabled(){};
    void onUpdate(float deltaTimeMs){
      Sprite->angle += deltaTimeMs/1000*0.5;
    };
    void onFixedUpdate(){};
    void onGUI(){};
    void onDestroy(){};
  };
}
