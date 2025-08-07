#pragma once

#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <map>

#include "../core/Action.h"
#include "../core/State.h"
#include "../core/entities/EntityManager.h"

class GameState : public State {
 private:
  EntityManager entityManager;
  Entity* player;

  sf::Texture textureBackground;
  sf::Sprite spriteBackground;

  float playerSpeed;
  // TODO: Move keyAction, binding register in State mother class for more
  // flexibility
  std::map<sf::Keyboard::Scancode, Action> keyAction;

 public:
  static const float CIRCLE_SIZE;

  GameState(Context context);

  void update(const sf::Time& deltaTime) override;

  void render() override;

  void handleInput(const sf::Event& event) override;

  void handleRealtimeInput(const sf::Time& deltaTime) override;

  void sAnimation(Entity* e, const sf::Time& dt);

  void sMovement(Entity* e, const sf::Time& dt);

  void initializeKeymap();

  void spawnPlayer();

  void spawnEnemies();
};
