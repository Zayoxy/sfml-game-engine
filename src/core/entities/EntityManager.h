#pragma once

#include <string>
#include <vector>

#include "Entity.h"

using EntitiesVec = std::vector<Entity*>;

class EntityManager {
 private:
  EntitiesVec entities;
  size_t nextID;

 public:
  static const size_t DEFAULT_ENTITIES_VEC_SIZE;

  EntityManager();
  virtual ~EntityManager();

  Entity* addEntity(const std::string& tag);

  void removeEntity(size_t id);

  Entity* getEntity(size_t id) const;

  EntitiesVec& getEntities();

 private:
  void cleanupEntities();
};
