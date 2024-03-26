#include "SpinnyCat.hpp"
#include <SFML/System/Vector2.hpp>
#include <cstdlib>

void SpinnyCat::create(){
  this->Position = sf::Vector2<float>(640,360);
}

void SpinnyCat::update(float deltaTimeMs){
  float deltaSec = deltaTimeMs/1000;
  this->Sprite->angle += deltaSec*0.5;
  this->Position.x += (rand()%11-5)*deltaSec;
  this->Position.y += (rand()%11-5)*deltaSec;
}
