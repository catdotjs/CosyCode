#include "example/SpinnyCat.hpp"
#include "src/Game.hpp"

void startMethod(cc::Game *game) {
  // Fix UUID system
  SpinnyCat *obj = new SpinnyCat("assets/test.jpg");
  game->AppendGameObject(obj);
}
int main(int argc, char *argv[]) {
  cc::Game game(cc::Vector2<int>(1280, 720), "Hello Test");
  game.onGameStart = startMethod;
  game.Start();
  return 0;
}
