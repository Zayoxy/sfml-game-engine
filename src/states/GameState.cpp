#include "GameState.h"

#include <iostream>

#include "../core/animations/CircleShapeAnimation.h"

const float GameState::CIRCLE_SIZE = 50.f;

GameState::GameState(Context context)
    : State(context),
      playerSpeed(300.f),
      keyAction(),
      entityManager(),
      textureBackground("assets/background.png"),
      spriteBackground(textureBackground) {
  initializeKeymap();
  spawnPlayer();
  spawnEnemies();
}

void GameState::update(const sf::Time& deltaTime) {
  auto& actionQueue = this->getContext().actionQueue;

  // Process ALL actions in the queue before rendering
  while (!actionQueue.empty()) {
    actionQueue.front().execute(*this->player, deltaTime);
    actionQueue.pop();
  }

  for (auto& entity : this->entityManager.getEntities()) {
    sAnimation(entity, deltaTime);
    sMovement(entity, deltaTime);
  }
}

void GameState::render() {
  Context& context = this->getContext();

  // Background
  context.target.draw(this->spriteBackground);

  for (auto* entity : this->entityManager.getEntities()) {
    assert(entity->hasComponent<CTransform>());
    auto& canim = entity->getComponent<CAnimation>();
    assert(canim.getAnimation() != nullptr);

    canim.getAnimation()->draw(context.target);
  }
}

void GameState::handleInput(const sf::Event& event) {}

void GameState::handleRealtimeInput(const sf::Time& deltaTime) {
  for (auto& [key, action] : keyAction) {
    if (sf::Keyboard::isKeyPressed(key)) {
      this->getContext().actionQueue.push(action);
    }
  }
}

void GameState::sAnimation(Entity* e, const sf::Time& dt) {
  assert(e->hasComponent<CTransform>());

  auto& canim = e->getComponent<CAnimation>();
  assert(canim.getAnimation() != nullptr);

  canim.getAnimation()->update(dt);
}

void GameState::sMovement(Entity* e, const sf::Time& dt) {
  if (!e->hasComponent<CTransform>()) return;

  auto& transform = e->getComponent<CTransform>();

  if (transform.velocity.length() <= 0.f) return;

  transform.velocity = transform.velocity.normalized() * playerSpeed;
  transform.position += transform.velocity * dt.asSeconds();

  // Reset velocity only if entity is the player
  if (e == this->player) {
    transform.velocity = {0.f, 0.f};
  }
}

void GameState::initializeKeymap() {
  struct PlayerMovement {
    sf::Vector2f velocity;

    PlayerMovement(float vx, float vy) : velocity(vx, vy) {}

    void operator()(Entity& entity, const sf::Time& dt) {
      assert(entity.hasComponent<CTransform>());
      auto& transform = entity.getComponent<CTransform>();
      transform.velocity += velocity.normalized() * velocity.length();
    }
  };

  keyAction[sf::Keyboard::Scancode::W] =
      Action(PlayerMovement(0.f, -playerSpeed));
  keyAction[sf::Keyboard::Scancode::A] =
      Action(PlayerMovement(-playerSpeed, 0.f));
  keyAction[sf::Keyboard::Scancode::S] =
      Action(PlayerMovement(0.f, playerSpeed));
  keyAction[sf::Keyboard::Scancode::D] =
      Action(PlayerMovement(playerSpeed, 0.f));
}

void GameState::spawnPlayer() {
  this->player = this->entityManager.addEntity("Player");

  // Middle of the window
  sf::Vector2f startPos = this->getContext().target.getView().getCenter();

  auto& transform = this->player->getComponent<CTransform>();
  transform.position = startPos;
  auto& canim = this->player->getComponent<CAnimation>();
  canim.setAnimation(new CircleShapeAnimation(transform, CIRCLE_SIZE, 8,
                                              sf::Color::Transparent,
                                              sf::Color::Red, 2.f, 3.f));
}

void GameState::spawnEnemies() {
  // TODO: Implement enemy spawning logic just testing for now
  auto* entityTest = this->entityManager.addEntity("Test");

  entityTest->getComponent<CAnimation>().setAnimation(new CircleShapeAnimation(
      entityTest->getComponent<CTransform>(), CIRCLE_SIZE, 3,
      sf::Color::Transparent, sf::Color::Green, 2.f, 5.f));
  entityTest->getComponent<CTransform>().scale = {2.f, 2.f};
  entityTest->getComponent<CTransform>().velocity = {3.f, 1.f};
}
