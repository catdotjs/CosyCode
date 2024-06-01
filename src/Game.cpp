#include "Game.hpp"
#include "GameObject.hpp"

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Window/VideoMode.hpp>
#include <SFML/Window/WindowBase.hpp>
#include <SFML/Window/WindowStyle.hpp>

// #include <imgui/imgui.h>
// #include "../lib/imgui-sfml/imgui-SFML.h"

#include <algorithm>
#include <functional>
#include <iostream>
#include <string>
#include <vector>

void cc::Game::AppendGameObject(cc::GameObject *object) {
  serialQueue.push_back(object);
}

void cc::Game::DestroyGameObject(cc::GameObject *object) {
  auto obj = std::find(objects.begin(), objects.end(), object);

  // Making sure last element is not given as output!
  if (obj != objects.end()) {
    // Destroy event will clear the queue
    destroyQueue.push_back(*obj);
    objects.erase(obj);
  }
}

void cc::Game::Start() {
  state = Starting;
  try {
    startWindow();
    startPhysics();
    startGUI();
    onGameStart(this);
  } catch (const std::exception &e) {
    std::cout << e.what() << "\n";
  }
  _StartGameLoop();
}

void cc::Game::Pause() { state = cc::GameState::Paused; }

void cc::Game::Stop() { state = cc::GameState::Exiting; }

void cc::Game::startWindow() {
  videoMode = new sf::VideoMode(windowSize.x, windowSize.y);
  window = new sf::RenderWindow(*videoMode, windowTitle, sf::Style::Titlebar);
}

void cc::Game::startPhysics() {}

void cc::Game::startGUI() {}

void cc::Game::onSerialise() {
  for (const auto &obj : serialQueue) {
    obj->UUID = UUIDgen();
    objects.push_back(obj);
    obj->onCreate();

    if (obj->Enabled) {
      obj->onEnabled();
    }
  }
  serialQueue.clear();
}

void cc::Game::onLoadLevel() {}

void cc::Game::onDestroy() {
  for (const auto &obj : destroyQueue) {
    delete obj;
  }
  destroyQueue.clear();
}

void cc::Game::onInput() {
  while (window->pollEvent(event)) {
    if (event.type == sf::Event::Closed) {
      state = cc::GameState::Exiting;
    }

    if (event.type == sf::Event::Resized) {
      windowSize = cc::Vector2<int>(event.size.width, event.size.height);
    }
  }
}

void cc::Game::onGUI() {
  onGameGUI(this);
  for (const auto &obj : objects) {
    obj->onGUI();
  }
}

void cc::Game::onRender() {
  window->clear(sf::Color::Red);
  onGameEarlyRender(this);
  for (const auto &obj : objects) {
    obj->Sprite->sprite.setPosition(obj->Position);
    obj->Sprite->sprite.setRotation(obj->Sprite->angle);
    window->draw(obj->Sprite->sprite);
  }
  onGameLateRender(this);
  window->display();
}

void cc::Game::onUpdate(float deltaTimeMs) {
  onGameUpdate(this, deltaTimeMs);
  for (const auto &obj : objects) {
    obj->onUpdate(deltaTimeMs);
  }
}

void cc::Game::onFixedUpdate() {
  onGameFixedUpdate(this);
  for (const auto &obj : objects) {
    obj->onFixedUpdate();
  }
}

void cc::Game::onDeserialise() {}

void cc::Game::runBacklogMethods() {
  for (const auto &blMethod : backlogMethods) {
    blMethod(); // Methods already have everything ready just needs to be run at
                // start of next frame
  }
  backlogMethods.clear();
}

// Get/Set Methods
void cc::Game::SetFullscreen(bool setFullscreen) {
  // We prep the package basically
  backlogMethods.push_back(
      [this, setFullscreen]() { this->_FullscreenSet(setFullscreen); });
}

/// WINDOW TITLE
std::string cc::Game::GetWindowTitle() { return windowTitle; }

void cc::Game::SetWindowTitle(std::string newTitle) {
  backlogMethods.push_back([this, newTitle]() {
    this->window->setTitle(newTitle);
    this->windowTitle = newTitle;
  });
}

/// WINDOW SIZE
cc::Vector2<int> cc::Game::GetWindowSize() {
  // Just updating it in case I forgot to update it somewhere else
  windowSize = cc::Vector2<int>(window->getSize());
  return windowSize;
}

void cc::Game::SetWindowSize(cc::Vector2<int> newSize) {
  windowSize = newSize;
  window->setSize(windowSize);
}

// Hidden Methods
void cc::Game::_FullscreenSet(bool setFullscreen) {
  window->create(*videoMode, windowTitle,
                 setFullscreen ? sf::Style::Fullscreen : sf::Style::Default);
}

void cc::Game::_StartGameLoop() {
  state = Running;
  int lastDelta = 0;
  try {
    while (state == Running) {
      runBacklogMethods();
      onSerialise();
      onLoadLevel();
      onDestroy();
      onInput();
      onGUI();
      onRender();

      // Update Logics
      lastDelta = frameClock.getElapsedTime().asMilliseconds() - lastDelta;
      onUpdate(lastDelta);

      if (frameClock.getElapsedTime().asMilliseconds() >
          FixedUpdateIntervalMs) {
        onFixedUpdate();
        frameClock.restart();
        lastDelta = 0;
      }
      onDeserialise();
    }
  } catch (const std::exception &e) {
    std::cout << e.what() << "\n";
  }
  _ProcessState();
}

void cc::Game::_ProcessState() {
  switch (state) {
  case cc::GameState::Running:
    _StartGameLoop();
    break;

  case cc::GameState::Paused:
    _Paused();
    break;

  case cc::GameState::Exiting:
    _Exiting();
    break;

  case cc::GameState::Destroying:
    _Destroy();
    break;
  default:
    window->close();
    break;
  }
}

// Future use!

void cc::Game::_Paused() {
  // Legit just idle
  while (state == cc::GameState::Paused) {
  }
  _ProcessState();
}

void cc::Game::_Exiting() {
  // Final deserialising will happen here
  state = cc::GameState::Exiting;
  _ProcessState();
}

void cc::Game::_Destroy() {
  // Destroy all
  window->close();
}
