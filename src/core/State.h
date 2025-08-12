
#pragma once

#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/System/Time.hpp>
#include <SFML/Window/Event.hpp>
#include <map>
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

  using KeyMap = std::map<sf::Keyboard::Scancode, Action>;

 private:
  Context context;
  KeyMap keyAction;

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

  /// @brief Add key-action mapping
  /// @param key Keyboard key
  /// @param action Action to be executed
  void registerKeyAction(sf::Keyboard::Scancode key, Action action);

  KeyMap& getKeyMap() const;

  Context& getContext() const;
};
