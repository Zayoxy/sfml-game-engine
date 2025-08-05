#include "GameEngine.h"

#include "../states/GameState.h"

const sf::Time GameEngine::PHYSICS_UPDATE_RATE = sf::seconds(1.f / 60.f);

GameEngine::GameEngine()
    : window(sf::VideoMode({800, 640}), "SFML Game"), currentState(nullptr) {
  window.setKeyRepeatEnabled(false);
  this->changeState(new GameState({*this, this->window}));
}

GameEngine::~GameEngine() {
  if (this->currentState != nullptr) {
    delete this->currentState;
  }
}

void GameEngine::run() {
  sf::Clock clock;
  sf::Time lag = sf::Time::Zero;

  while (window.isOpen()) {
    sf::Time deltaTime = clock.restart();
    lag += deltaTime;

    // Ensure the game runs at a fixed physics update rate
    while (lag > PHYSICS_UPDATE_RATE) {
      lag -= PHYSICS_UPDATE_RATE;

      processEvents();
      update(PHYSICS_UPDATE_RATE);
    }

    render();
  }
}

void GameEngine::changeState(State* newState) {
  if (this->currentState != nullptr) {
    delete this->currentState;
  }

  this->currentState = newState;
}

void GameEngine::processEvents() {
  while (const std::optional<sf::Event> event = window.pollEvent()) {
    if (event->is<sf::Event::Closed>()) {
      window.close();
    } else {
      currentState->handleInput(*event);
    }
  }
}

void GameEngine::update(const sf::Time& deltaTime) {
  currentState->update(deltaTime);
}

void GameEngine::render() {
  window.clear();          // Clear forward window buffer
  currentState->render();  // Render the current state
  window.display();        // Display drawn frame to the screen
}
