#include "GameState.h"

#include <iostream>

#include "../core/animations/CircleShapeAnimation.h"

const float GameState::CIRCLE_SIZE = 50.f;

GameState::GameState(Context context)
    : State(context),
      playerSpeed(300.f),
      keymapPressed(),
      entityManager(),
      textureBackground("assets/background.png"),
      spriteBackground(textureBackground) {
  // this->entityManager.addEntity("Test");
  this->player = this->entityManager.addEntity("Player");

  // Middle of the window
  sf::Vector2f startPos = this->getContext().target.getView().getCenter() /*-
                          sf::Vector2f(CIRCLE_SIZE, CIRCLE_SIZE)*/
      ;

  auto& transform = this->player->getComponent<CTransform>();
  transform.position = startPos;
  auto& canim = this->player->getComponent<CAnimation>();
  canim.setAnimation(new CircleShapeAnimation(transform, CIRCLE_SIZE, 8,
                                              sf::Color::Transparent,
                                              sf::Color::Red, 2.f, 3.f));

  initializeKeymap();
}

void GameState::update(const sf::Time& deltaTime) {
  for (auto& entity : this->entityManager.getEntities()) {
    sAnimation(entity, deltaTime);
  }

  // Movement system
  if (!this->player->hasComponent<CTransform>()) return;

  auto& transform = this->player->getComponent<CTransform>();
  transform.velocity = {0.f, 0.f};

  if (keymapPressed[sf::Keyboard::Scancode::W]) {
    transform.velocity.y -= 1.f;
  }
  if (keymapPressed[sf::Keyboard::Scancode::A]) {
    transform.velocity.x -= 1.f;
  }
  if (keymapPressed[sf::Keyboard::Scancode::S]) {
    transform.velocity.y += 1.f;
  }
  if (keymapPressed[sf::Keyboard::Scancode::D]) {
    transform.velocity.x += 1.f;
  }

  if (transform.velocity.length() <= 0.f) return;

  transform.velocity =
      transform.velocity.normalized() * playerSpeed * deltaTime.asSeconds();
  transform.position += transform.velocity;
}

void GameState::render() {
  Context& context = this->getContext();

  // Background
  context.target.draw(this->spriteBackground);

  assert(this->player->hasComponent<CTransform>());
  auto& canim = this->player->getComponent<CAnimation>();
  assert(canim.getAnimation() != nullptr);

  canim.getAnimation()->draw(context.target);
}

void GameState::handleInput(const sf::Event& event) {
  // Handle key pressed events
  if (const auto& keyPressedEvent = event.getIf<sf::Event::KeyPressed>()) {
    handlePlayerInput(keyPressedEvent->scancode, true);
  }

  if (const auto& keyReleasedEvent = event.getIf<sf::Event::KeyReleased>()) {
    handlePlayerInput(keyReleasedEvent->scancode, false);
  }
}

void GameState::sAnimation(Entity* e, const sf::Time& dt) {
  assert(e->hasComponent<CTransform>());

  auto& canim = e->getComponent<CAnimation>();
  assert(canim.getAnimation() != nullptr);

  canim.getAnimation()->update(dt);
}

void GameState::initializeKeymap() {
  keymapPressed[sf::Keyboard::Scancode::W] = false;
  keymapPressed[sf::Keyboard::Scancode::A] = false;
  keymapPressed[sf::Keyboard::Scancode::S] = false;
  keymapPressed[sf::Keyboard::Scancode::D] = false;
}

void GameState::handlePlayerInput(sf::Keyboard::Scancode key, bool pressed) {
  if (key == sf::Keyboard::Scancode::W) {
    keymapPressed[sf::Keyboard::Scancode::W] = pressed;
  }
  if (key == sf::Keyboard::Scancode::A) {
    keymapPressed[sf::Keyboard::Scancode::A] = pressed;
  }
  if (key == sf::Keyboard::Scancode::S) {
    keymapPressed[sf::Keyboard::Scancode::S] = pressed;
  }
  if (key == sf::Keyboard::Scancode::D) {
    keymapPressed[sf::Keyboard::Scancode::D] = pressed;
  }
}
