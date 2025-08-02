#include <SFML/Graphics.hpp>
#include <map>

class Game {
 private:
  sf::RenderWindow window;

  sf::CircleShape circle;
  float circleSpeed;
  std::map<sf::Keyboard::Scancode, bool> keymapPressed;

 public:
  static const uint16_t FRAMERATE_LIMIT;
  static const float CIRCLE_SIZE;
  static const sf::Time PHYSICS_UPDATE_RATE;

  Game();
  virtual ~Game() = default;

  void run();

 private:
  void processEvents();

  /// @brief Physics update of the game
  /// @param deltaTime Time since last update to be constant
  void update(sf::Time deltaTime);

  void render();

  void initializeKeymap();

  void handlePlayerInput(sf::Keyboard::Scancode key, bool pressed);
};