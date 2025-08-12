#pragma once

#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>

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
