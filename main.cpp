#include "src/Game.hpp"
#include <SFML/System/Vector2.hpp>

#include "example/SpinnyCat.hpp"

void startMethod(cc::Game* game){
  // Fix UUID system
  SpinnyCat* obj = new SpinnyCat("assets/test.jpg");
  game->AppendGameObject(obj);
}
int main (int argc, char *argv[]) {
  cc::Game* game = new cc::Game(sf::Vector2<int>(1280, 720),"Hello Test");
  game->onGameStart = startMethod;
  game->Start();
  return 0;
}
