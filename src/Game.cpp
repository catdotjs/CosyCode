#include "Game.hpp"
#include "GameObject.hpp"
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/VideoMode.hpp>
#include <SFML/Window/WindowStyle.hpp>

#include <string>
#include <vector>
#include <functional>
#include <iostream>

void cc::Game::AppendGameObject(cc::GameObject* object){
  serialQueue.push_back(object);
}

void cc::Game::Start(){
  state = Starting;
  try{
    startWindow();
    startPhysics();
    startGUI();
    state = Running;
    AppendGameObject(new cc::GameObject("assets/test.jpg"));
    while (state == Running) {
      runBacklogMethods();
      onSerialise();
      onLoadLevel();
      onDestroy();
      onInput();
      onGUI();
      onRender();
      onUpdate();
      if (frameClock.getElapsedTime().asMilliseconds()>FixedUpdateIntervalMs) {
        onFixedUpdate();
        frameClock.restart();
      }
      onDeserialise();
    }
  }catch(const std::exception& e){
    std::cout << e.what() << "\n";
  }
}

void cc::Game::startWindow(){
  videoMode = new sf::VideoMode(windowSize.x, windowSize.y);
  window = new sf::RenderWindow(*videoMode, windowTitle, sf::Style::Titlebar); 
}

void cc::Game::startPhysics(){

}

void cc::Game::startGUI(){

}

void cc::Game::onSerialise(){
  for (const auto& obj : serialQueue){ 
    obj->UID = 1;
    objects.push_back(obj);
  }
  serialQueue.clear();
}

void cc::Game::onLoadLevel(){

}

void cc::Game::onDestroy(){

}

void cc::Game::onInput(){

}

void cc::Game::onGUI(){

}

void cc::Game::onRender(){
  window->clear(sf::Color::Red);
  for(const auto& obj : objects){
    obj->Position = (sf::Vector2<float>)(windowSize/2);
    obj->Sprite->sprite.setPosition(obj->Position);
    window->draw(obj->Sprite->sprite);
  }
  window->display();
}

void cc::Game::onUpdate(){

}

void cc::Game::onFixedUpdate(){

}

void cc::Game::onDeserialise(){

}



// Get/Set Methods 
void cc::Game::SetFullscreen(bool setFullscreen){
  // We prep the package basically
  backlogMethods.push_back([this, setFullscreen](){ this->_FullscreenSet(setFullscreen); });
}

/// WINDOW TITLE
std::string cc::Game::GetWindowTitle(){return windowTitle;}

void cc::Game::SetWindowTitle(std::string newTitle){
  backlogMethods.push_back([this, newTitle](){ 
      this->window->setTitle(newTitle);
      this->windowTitle=newTitle;
  });
}

/// WINDOW SIZE
sf::Vector2<int> cc::Game::GetWindowSize(){
  // Just updating it in case I forgot to update it somewhere else
  windowSize = (sf::Vector2<int>)window->getSize();
  return windowSize;
}

void cc::Game::SetWindowSize(sf::Vector2<int> newSize){
  windowSize = newSize;
  window->setSize(sf::Vector2u(windowSize.x,windowSize.y));
}



// Quick Methods
void cc::Game::_FullscreenSet(bool setFullscreen){
  window->create(*videoMode, windowTitle, setFullscreen?sf::Style::Fullscreen:sf::Style::Default);
}

void cc::Game::runBacklogMethods(){
  for(const auto& blMethod : backlogMethods){
    blMethod(); // Methods already have everything ready just needs to be run at start of next frame
  }
  backlogMethods.clear();
}
