#include "State.h"

State::State(State::Context context) : context(context) {}

State::Context& State::getContext() const {
  return const_cast<State::Context&>(this->context);
}