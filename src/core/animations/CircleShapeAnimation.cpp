#include "CircleShapeAnimation.h"

#include <SFML/System/Angle.hpp>

CircleShapeAnimation::CircleShapeAnimation(CTransform& transform, float radius,
                                           size_t points, sf::Color fillColor,
                                           sf::Color outlineColor,
                                           float outlineThickness,
                                           float rotationSpeed)
    : Animation(transform),
      circleShape(radius, points),
      rotationSpeed(rotationSpeed) {
  this->circleShape.setFillColor(fillColor);
  this->circleShape.setOrigin({radius, radius});  // Set origin to center
  this->circleShape.setOutlineColor(outlineColor);
  this->circleShape.setOutlineThickness(outlineThickness);
}

void CircleShapeAnimation::draw(sf::RenderTarget& target) {
  // https://www.sfml-dev.org/tutorials/3.0/system/angle/
  this->circleShape.setRotation(sf::radians(this->transform.rotation));
  this->circleShape.setPosition(this->transform.position);
  this->circleShape.setScale(this->transform.scale);

  target.draw(this->circleShape);
}

void CircleShapeAnimation::update(const sf::Time& deltaTime) {
  this->transform.rotation += this->rotationSpeed * deltaTime.asSeconds();
}
