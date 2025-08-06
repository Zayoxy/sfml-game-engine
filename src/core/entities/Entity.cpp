#include "Entity.h"

Entity::Entity(size_t id, const std::string& tag) : id(id), tag(tag) {}

size_t Entity::getID() const { return this->id; }

std::string& Entity::getTag() const {
  return const_cast<std::string&>(this->tag);
}
