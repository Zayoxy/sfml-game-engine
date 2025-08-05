#pragma once

#include <SFML/Graphics.hpp>

#include "State.h"

class GameEngine {
 private:
  sf::RenderWindow window;
  State* currentState;

 public:
  static const uint16_t FRAMERATE_LIMIT;
  static const sf::Time PHYSICS_UPDATE_RATE;

  GameEngine();
  virtual ~GameEngine();

  void run();

  void changeState(State* newState);

 private:
  void processEvents();

  /// @brief Physics update of the game
  /// @param deltaTime Time since last update to be constant
  void update(const sf::Time& deltaTime);

  void render();

  void initializeKeymap();

  void handlePlayerInput(sf::Keyboard::Scancode key, bool pressed);
};