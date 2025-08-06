#pragma once

#include <SFML/Graphics/CircleShape.hpp>

#include "Animation.h"

class CircleShapeAnimation : public Animation {
 private:
  sf::CircleShape circleShape;
  float rotationSpeed;

 public:
  CircleShapeAnimation(CTransform& transform, float radius, size_t points,
                       sf::Color fillColor, sf::Color outlineColor,
                       float outlineThickness, float rotationSpeed);

  void draw(sf::RenderTarget& target) override;

  void update(const sf::Time& deltaTime) override;
};
