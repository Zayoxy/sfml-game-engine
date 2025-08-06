#pragma once

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/System/Time.hpp>

#include "../components/CTransform.h"

class Animation {
 public:
  Animation(CTransform& transform);

  virtual ~Animation() = default;

  virtual void draw(sf::RenderTarget& target) = 0;

  virtual void update(const sf::Time& deltaTime) = 0;

 protected:
  CTransform& transform;
};
