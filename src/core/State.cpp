#include "State.h"

State::State(State::Context context) : context(context), keyAction() {}

void State::registerKeyAction(sf::Keyboard::Scancode key, Action action) {
  assert(this->keyAction.find(key) == this->keyAction.end());
  this->keyAction[key] = action;
}

State::KeyMap& State::getKeyMap() const {
  return const_cast<KeyMap&>(this->keyAction);
}

State::Context& State::getContext() const {
  return const_cast<State::Context&>(this->context);
}