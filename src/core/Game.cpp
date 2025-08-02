#include "Game.h"

const uint16_t Game::FRAMERATE_LIMIT = 240;
const float Game::CIRCLE_SIZE = 50.f;
const sf::Time Game::PHYSICS_UPDATE_RATE = sf::seconds(1.f / 60.f);

Game::Game()
    : window(sf::VideoMode({800, 640}), "SFML Game"),
      circle(CIRCLE_SIZE),
      circleSpeed(300.f),
      keymapPressed() {
  window.setFramerateLimit(FRAMERATE_LIMIT);
  window.setKeyRepeatEnabled(false);

  // Middle of the window
  circle.setPosition(window.getView().getCenter() -
                     sf::Vector2f(CIRCLE_SIZE, CIRCLE_SIZE));

  circle.setFillColor(sf::Color::Magenta);

  initializeKeymap();
}

void Game::run() {
  sf::Clock clock;
  sf::Time timeSinceLastUpdate = sf::Time::Zero;

  while (window.isOpen()) {
    sf::Time deltaTime = clock.restart();
    timeSinceLastUpdate += deltaTime;

    // Ensure the game runs at a fixed physics update rate
    while (timeSinceLastUpdate > PHYSICS_UPDATE_RATE) {
      timeSinceLastUpdate -= PHYSICS_UPDATE_RATE;

      processEvents();
      update(PHYSICS_UPDATE_RATE);
    }

    render();
  }
}

void Game::processEvents() {
  while (const std::optional event = window.pollEvent()) {
    if (event->is<sf::Event::Closed>()) {
      window.close();
    }

    // Handle key pressed events
    if (const auto* keyPressedEvent = event->getIf<sf::Event::KeyPressed>()) {
      handlePlayerInput(keyPressedEvent->scancode, true);
    }

    if (const auto* keyReleasedEvent = event->getIf<sf::Event::KeyReleased>()) {
      handlePlayerInput(keyReleasedEvent->scancode, false);
    }
  }
}

void Game::update(sf::Time deltaTime) {
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

void Game::render() {
  window.clear();
  window.draw(circle);
  window.display();
}

void Game::initializeKeymap() {
  keymapPressed[sf::Keyboard::Scancode::W] = false;
  keymapPressed[sf::Keyboard::Scancode::A] = false;
  keymapPressed[sf::Keyboard::Scancode::S] = false;
  keymapPressed[sf::Keyboard::Scancode::D] = false;
}

void Game::handlePlayerInput(sf::Keyboard::Scancode key, bool pressed) {
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
