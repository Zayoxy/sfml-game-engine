#include "GameState.h"

const float GameState::CIRCLE_SIZE = 50.f;

GameState::GameState(Context context)
    : State(context), circle(CIRCLE_SIZE), circleSpeed(300.f), keymapPressed() {
  // Middle of the window
  circle.setPosition(this->getContext().target.getView().getCenter() -
                     sf::Vector2f(CIRCLE_SIZE, CIRCLE_SIZE));

  circle.setFillColor(sf::Color::Magenta);

  initializeKeymap();
}

void GameState::update(const sf::Time& deltaTime) {
  sf::Vector2f movement(0.f, 0.f);

  if (keymapPressed[sf::Keyboard::Scancode::W]) {
    movement.y -= 1.f;
  }
  if (keymapPressed[sf::Keyboard::Scancode::A]) {
    movement.x -= 1.f;
  }
  if (keymapPressed[sf::Keyboard::Scancode::S]) {
    movement.y += 1.f;
  }
  if (keymapPressed[sf::Keyboard::Scancode::D]) {
    movement.x += 1.f;
  }

  if (movement.length() <= 0.f) return;

  movement = movement.normalized();

  circle.move(movement * circleSpeed * deltaTime.asSeconds());
}

void GameState::render() {
  Context& context = this->getContext();

  context.target.draw(circle);
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
