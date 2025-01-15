#pragma once
#include "animation.hpp"
#include "raylib.h"
#include <memory>

class World;

class Entity {
public:
  enum class Face { LEFT, RIGHT };
  enum class State { HIT, DIE, MOVE, STAND, SKILL, ATTACK };

  std::weak_ptr<World> world{};

  virtual ~Entity() = default;
  virtual Face GetFace() const noexcept final { return M_face; }
  virtual unsigned GetHP() const noexcept final { return M_hp; }
  virtual unsigned GetMP() const noexcept final { return M_mp; }
  virtual bool GetGround() const noexcept final { return M_ground; }
  virtual State GetState() const noexcept final { return M_state; }
  virtual Vector2 GetPosition() const noexcept final { return M_position; }
  virtual Vector2 GetVelocity() const noexcept final { return M_velocity; }
  virtual void Update() final;
  virtual void Render() final;

protected:
  float jump = 0.f;
  float speed = 0.f;
  float width = 0.f;
  float height = 0.f;

  virtual void OnUpdate() = 0;
  virtual void OnRender() = 0;

  template <size_t N> void Animate(Animation<N> &animation) {
    switch (M_face) {
    case Face::LEFT:
      animation.template Draw<Animation<N>::Option::NONE>(M_position);
      break;
    case Face::RIGHT:
      animation.template Draw<Animation<N>::Option::FLIP>(M_position);
      break;
    }
  }

  enum class Direction { LEFT, RIGHT, JUMP };

  template <Direction D> void Move() noexcept {
    if constexpr (D == Direction::LEFT) {
      M_velocity.x = -speed;
      M_face = Face::LEFT;
    } else if constexpr (D == Direction::RIGHT) {
      M_velocity.x = +speed;
      M_face = Face::RIGHT;
    } else {
      if (M_ground) {
        M_velocity.y = -jump;
      }
    }
  }

private:
  Face M_face = Face::LEFT;
  bool M_ground = false;
  unsigned M_hp = 100U;
  unsigned M_mp = 100U;
  State M_state{};
  Vector2 M_position{};
  Vector2 M_velocity{};
};