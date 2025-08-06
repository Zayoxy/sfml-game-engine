#pragma once

#include <SFML/System/Vector2.hpp>

#include "Component.h"

class CTransform : public Component {
 public:
  sf::Vector2f position;
  sf::Vector2f scale = {1.f, 1.f};
  sf::Vector2f velocity = {0.f, 0.f};
  float rotation = 0.f;  // in radian

  CTransform(const sf::Vector2f& position = {0.f, 0.f}) : position(position) {}

  CTransform(const sf::Vector2f& position, const sf::Vector2f& scale,
             const sf::Vector2f& velocity, float rotation)
      : position(position),
        scale(scale),
        velocity(velocity),
        rotation(rotation) {}
};
