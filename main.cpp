#include "src/Game.hpp"
#include <SFML/System/Vector2.hpp>

int main (int argc, char *argv[]) {
  cc::Game* game = new cc::Game(sf::Vector2<int>(1280, 720),"Hello Test");
  game->Start();
  return 0;
}
