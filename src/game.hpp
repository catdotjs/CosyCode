#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/Window/Window.hpp>
#include <cstdint>
#include <iostream>
#include <exception>

#include <SFML/Main.hpp>
#include <SFML/System.hpp>

enum GameState{
  Starting,
  Running,
  Paused,
  Exiting,
  Destroying
};

class Game{
  public:
  int16_t FixedUpdateIntervalMs = 50;
  void Start(){
    state = Starting;
    try{
      startWindow();
      startPhysics();
      startGUI();
      state = Running;

      while (state == Running) {
        window->clear(sf::Color::Black);
        frameClock.restart();
        onSerialise();
        onLoadLevel();
        onDestroy();
        while (frameClock.getElapsedTime().asMilliseconds()<FixedUpdateIntervalMs) {
          onInput();
          onGUI();
          onRender();
          onUpdate();
        }
        onFixedUpdate();
        onDeserialise();
        window->display();
      }
    }catch(const std::exception& e){
      std::cout << e.what() << "\n";
    }
  }

  private:
  sf::Clock frameClock;
  GameState state;
  sf::RenderWindow* window;
  void startWindow();
  void startPhysics();
  void startGUI();

  void onSerialise();      // Frame timer starts here
  void onLoadLevel();
  void onDestroy();
  void onInput();
  void onGUI();            // This is here due to needing onInput
  void onRender();    
  void onUpdate();
  void onFixedUpdate();    // Update can run several times per 1 fixedUpdate
  void onDeserialise();    // Frame timer ends here
};
