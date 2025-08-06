#pragma once

#include "../animations/Animation.h"
#include "Component.h"

class CAnimation : public Component {
 private:
  Animation* animation;

  void cleanup() {
    if (animation != nullptr) {
      delete animation;
      animation = nullptr;
    }
  }

 public:
  CAnimation(Animation* animation = nullptr) : animation(animation) {}

  ~CAnimation() override { cleanup(); }

  void setAnimation(Animation* newAnimation) {
    cleanup();
    animation = newAnimation;
  }

  Animation* getAnimation() const { return animation; }
};