#include "Action.h"

Action::Action() : action(nullptr) {}

Action::Action(ActionDelegate action) : action(std::move(action)) {}