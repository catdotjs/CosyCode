#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/Window/VideoMode.hpp>
#include <SFML/Window/Window.hpp>
#include <SFML/Window/WindowBase.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Main.hpp>
#include <SFML/System.hpp>

#include <boost/uuid/random_generator.hpp>
#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_generators.hpp>

#include <functional>
#include <string>

#include <cstdint>
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
  sf::Event event;
  Game(sf::Vector2<int> windowsize, std::string title="No title", bool setfullscreen=false){
    windowSize = windowsize;
    windowTitle = title;
    SetFullscreen(setfullscreen);
  }

  void Start();
  void Pause();
  void Stop();

  // Easy to remove in Game class is static
  void AppendGameObject(cc::GameObject* object);
  void DestroyGameObject(cc::GameObject* object);
  void DestroyGameObject(boost::uuids::uuid UUID);

  // Control Window
  void SetFullscreen(bool isFullscreen);

  std::string GetWindowTitle();
  void SetWindowTitle(std::string newTitle);

  sf::Vector2<int> GetWindowSize();
  void SetWindowSize(sf::Vector2<int> newSize);

  // Game World Controls
  std::function<void(cc::Game*)> onGameStart = [](cc::Game*) {};
  std::function<void(cc::Game*,float)> onGameUpdate = [](cc::Game*, float) {};
  std::function<void(cc::Game*)> onGameFixedUpdate = [](cc::Game*) {};
  std::function<void(cc::Game*)> onGameGUI = [](cc::Game*) {};
  std::function<void(cc::Game*)> onGameEarlyRender = [](cc::Game*) {};
  std::function<void(cc::Game*)> onGameLateRender = [](cc::Game*) {};
  private:
  // Due to timing importances(specially rendering),
  // Programmer should only be able to change values here
  // by running methods. Methods will be properly run AT THE END of loop.

  // Core variables
  GameState state;
  std::vector<std::function<void()>> backlogMethods;
  
  // Objects
  boost::uuids::random_generator_pure UUIDgen;
  std::vector<GameObject*> serialQueue;
  std::vector<GameObject*> destroyQueue;
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
  void onGUI();           
  void onRender();    
  void onUpdate(float deltaTimeMs);
  void onFixedUpdate();    
  void onDeserialise();
  void runBacklogMethods();

  // Hidden Methods
  void _FullscreenSet(bool setFullscreen);
  void _StartGameLoop();
  void _ProcessState();
  void _Paused();
  void _Exiting();
  void _Destroy();
};
}
