#include "../src/GameObject.hpp"
#include <functional>
#include <string>

class SpinnyCat: public cc::GameObject{
  public:
  SpinnyCat(std::string spritesource) : cc::GameObject(spritesource){
    onCreate = std::bind(&SpinnyCat::create, this);
    onUpdate = std::bind(&SpinnyCat::update, this, std::placeholders::_1);
  };
  private:
  void create();
  void update(float deltaTimeMs);
};

