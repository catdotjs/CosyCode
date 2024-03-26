#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/Window/VideoMode.hpp>
#include <SFML/Window/Window.hpp>
#include <cstdint>

#include <SFML/Main.hpp>
#include <SFML/System.hpp>
#include <functional>
#include <string>

#include "GameObject.hpp"

namespace cc {
enum GameState{
  Starting,
  Running,
  Paused,
  Exiting,
  Destroying
};

class Game{
  public:
  Game(sf::Vector2<int> windowsize, std::string title="No title", bool setfullscreen=false){
    windowSize = windowsize;
    windowTitle = title;
    SetFullscreen(setfullscreen);
  }

  void Start();
  void Pause();

  // Easy to remove in Game class is static
  void AppendGameObject(cc::GameObject* object);

  // Control Window
  void SetFullscreen(bool isFullscreen);

  std::string GetWindowTitle();
  void SetWindowTitle(std::string newTitle);

  sf::Vector2<int> GetWindowSize();
  void SetWindowSize(sf::Vector2<int> newSize);
  private:
  // Due to timing importances(specially rendering),
  // Programmer should only be able to change values here
  // by running methods. Methods will be properly run AT THE END of loop.

  // Core variables
  GameState state;
  std::vector<std::function<void()>> backlogMethods;
  std::vector<GameObject*> serialQueue;
  std::vector<GameObject*> objects;
  
  // Timing
  sf::Clock frameClock;
  int16_t FixedUpdateIntervalMs = 50;
  
  // Windowing
  sf::VideoMode* videoMode;
  sf::RenderWindow* window;
  sf::Vector2<int> windowSize;
  std::string windowTitle;

  // Methods
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

  // Hidden Methods
  void _FullscreenSet(bool setFullscreen);

  void runBacklogMethods();
};
}
