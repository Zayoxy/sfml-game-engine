#include "EntityManager.h"

#include <algorithm>
#include <functional>

const size_t EntityManager::DEFAULT_ENTITIES_VEC_SIZE = 100;

EntityManager::EntityManager() : nextID(0), entities() {
  this->entities.reserve(DEFAULT_ENTITIES_VEC_SIZE);
}

EntityManager::~EntityManager() { this->cleanupEntities(); }

Entity* EntityManager::addEntity(const std::string& tag) {
  Entity* newEntity = new Entity(this->nextID++, tag);
  this->entities.push_back(newEntity);

  return newEntity;
}

void EntityManager::removeEntity(size_t id) {
  static const auto predicate = [id](const Entity* entity) {
    return id == entity->getID();
  };

  this->entities.erase(
      std::remove_if(this->entities.begin(), this->entities.end(), predicate));
}

Entity* EntityManager::getEntity(size_t id) const {
  static const auto it = std::find_if(
      this->entities.begin(), this->entities.end(),
      [id](const Entity* entity) { return entity->getID() == id; });

  // return entity* pointed by it (hence why *it) or nullptr if not found
  return (it != this->entities.end()) ? *it : nullptr;
}

EntitiesVec& EntityManager::getEntities() { return this->entities; }

void EntityManager::cleanupEntities() {
  for (auto* entity : getEntities()) {
    if (entity == nullptr) continue;

    delete entity;
  }

  this->entities.clear();
}
