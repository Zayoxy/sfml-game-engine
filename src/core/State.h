
#pragma once

#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/System/Time.hpp>
#include <SFML/Window/Event.hpp>

// Forward declaration to avoid circular dependency
class GameEngine;

class State {
 public:
  struct Context {
    GameEngine& gameEngine;
    sf::RenderTarget& target;
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

  virtual void handleInput(const sf::Event& event) = 0;

  Context& getContext() const;
};
