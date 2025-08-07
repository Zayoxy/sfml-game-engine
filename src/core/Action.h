#pragma once

#include <SFML/System/Time.hpp>
#include <functional>

#include "entities/Entity.h"

using ActionDelegate = std::function<void(Entity &, const sf::Time &)>;

class Action {
 private:
  ActionDelegate action;

 public:
  /// @brief Default constructor mandatory when using std::map or std::vector
  Action();

  Action(ActionDelegate action);

  virtual ~Action() = default;

  void execute(Entity &entity, const sf::Time &dt) { (*this)(entity, dt); }

  void operator()(Entity &entity, const sf::Time &dt) {
    if (!this->action) return;

    this->action(entity, dt);
  }
};
