
#pragma once

#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/System/Time.hpp>
#include <SFML/Window/Event.hpp>
#include <queue>

#include "Action.h"

// Forward declaration to avoid circular dependency
class GameEngine;

class State {
 public:
  struct Context {
    GameEngine& gameEngine;
    sf::RenderTarget& target;
    std::queue<Action>& actionQueue;
  };

 private:
  Context context;

 public:
  State(Context context);

  virtual ~State() = default;

  /// @brief Update game objects (physics, animations, etc) of the state
  /// @param deltaTime Time since last update
  virtual void update(const sf::Time& deltaTime) = 0;

  /// @brief Render state to target (i.g window)
  virtual void render() = 0;

  /// @brief Handle input events that are not real-time (i.e. key pressed, mouse
  /// clicked)
  /// @param event SFML Event
  virtual void handleInput(const sf::Event& event) {}

  /// @brief Handle real-time input events (i.e. key held down, mouse moved)
  /// @param deltaTime Time since last update
  virtual void handleRealtimeInput(const sf::Time& deltaTime) {}

  Context& getContext() const;
};
