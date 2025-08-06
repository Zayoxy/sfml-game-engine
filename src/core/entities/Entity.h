#pragma once

#include <string>
#include <tuple>
#include <variant>

#include "../../utils.h"
#include "../components/CAnimation.h"
#include "../components/CTransform.h"

class EntityManager;

/// @brief Entity class that represents an object in the game world.
/// Cannot instantiate directly, use EntityManager to create/delete entities.
class Entity {
  friend class EntityManager;

 private:
  size_t id;
  std::string tag;

  std::tuple<CTransform, CAnimation> components;

  Entity(size_t id, const std::string& tag);

 public:
  virtual ~Entity() = default;

  size_t getID() const;
  std::string& getTag() const;

  template <typename T>
  bool hasComponent() {
    return utils::tuple_contains<T, decltype(this->components)>::value;
  }

  /// @brief Get a component of the entity.
  /// @tparam T The type of the component.
  /// @return A REFERENCE to the component so we can modify it
  template <typename T>
  T& getComponent() {
    return std::get<T>(this->components);
  }
};
