#include <SFML/Graphics.hpp>
#include <cmath>
#include <iostream>

const uint16_t FRAMERATE_LIMIT = 240;

typedef struct {
  uint16_t width;
  uint16_t height;
} Dimension;

Dimension windowDimensions = {1920, 1080};

const float CIRCLE_SPEED = 60.f;

/// @brief Make circle move right to end of window and back to left side.
/// @param circle
void move_circle_right_left(sf::CircleShape& circle);

/// @brief Make the circle moveable with WASD keys.
/// @param circle
/// @param key
void control_circle(sf::CircleShape& circle, sf::Keyboard::Scancode key);

int main(void) {
  auto window = sf::RenderWindow(
      sf::VideoMode({windowDimensions.width, windowDimensions.height}),
      "CMake SFML Project");
  window.setFramerateLimit(FRAMERATE_LIMIT);

  // Create circle shape to be drawn
  const float CIRCLE_SIZE = 50.f;
  sf::CircleShape circle(CIRCLE_SIZE);
  circle.setPosition(
      window.getView().getCenter() -
      sf::Vector2f(CIRCLE_SIZE, CIRCLE_SIZE));  // Middle of the window
  circle.setFillColor(sf::Color::Magenta);

  while (window.isOpen()) {
    while (const std::optional event = window.pollEvent()) {
      if (event->is<sf::Event::Closed>()) {
        window.close();
      }

      // Handle key pressed events
      if (const auto* keyPressedEvent = event->getIf<sf::Event::KeyPressed>()) {
        control_circle(circle, keyPressedEvent->scancode);
      }
    }

    window.clear();
    // move_circle_right_left(circle);
    window.draw(circle);
    window.display();
  }
}

void move_circle_right_left(sf::CircleShape& circle) {
  sf::Vector2f pos = circle.getPosition();
  static sf::Vector2f movement{1.f, 0.f};  // Static so created only once

  if (pos.x >= windowDimensions.width - circle.getRadius() * 2 || pos.x <= 0) {
    movement.x *= -1.f;
  }

  //   std::cout << "Movement vector: " << movement.x << ", " << movement.y
  //             << std::endl;

  circle.move(movement);
}

void control_circle(sf::CircleShape& circle, sf::Keyboard::Scancode key) {
  sf::Vector2f movement(0.f, 0.f);
  switch (key) {
    case sf::Keyboard::Scancode::A:
      movement.x = -1.f;
      break;
    case sf::Keyboard::Scancode::D:
      movement.x = 1.f;
      break;
    case sf::Keyboard::Scancode::W:
      movement.y = -1.f;
      break;
    case sf::Keyboard::Scancode::S:
      movement.y = 1.f;
      break;
    default:
      std::cout << "Unknown key pressed: " << static_cast<int>(key)
                << std::endl;
      return;
      break;
  }

  circle.move(movement * CIRCLE_SPEED);
}