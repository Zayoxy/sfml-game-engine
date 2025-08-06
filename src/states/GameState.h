#pragma once

#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <map>

#include "../core/State.h"
#include "../core/entities/EntityManager.h"

class GameState : public State {
 private:
  EntityManager entityManager;
  Entity* player;

  sf::Texture textureBackground;
  sf::Sprite spriteBackground;

  float playerSpeed;
  std::map<sf::Keyboard::Scancode, bool> keymapPressed;

 public:
  static const float CIRCLE_SIZE;

  GameState(Context context);

  void update(const sf::Time& deltaTime) override;

  void render() override;

  void handleInput(const sf::Event& event) override;

  void initializeKeymap();

  void handlePlayerInput(sf::Keyboard::Scancode key, bool pressed);
};
