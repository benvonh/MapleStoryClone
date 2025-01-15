#include "entity.hpp"
#include "config.hpp"
#include "raylib.h"
#include "raymath.h"
#include "world.hpp"

void Entity::Update() {
  if (IsKeyPressed(KEY_R)) {
    M_position = Vector2Zero();
  }
  if (M_ground) {
    M_velocity.x = 0.f;
  }
  OnUpdate();

  const Vector2 dist = Vector2Scale(M_velocity, GetFrameTime());

  Vector2 newPos = Vector2Add(M_position, dist);

  if (const auto &w = this->world.lock()) {
    M_ground = false;
    Vector2 collisionPoint;

    const Vector2 left{.x = newPos.x - this->width / 2, .y = newPos.y};
    const Vector2 right{.x = newPos.x + this->width / 2, .y = newPos.y};
    // Collision due to wall
    for (size_t i = 1ull; i < w->M_colliders.size(); i++) {
      if (CheckCollisionLines(w->M_colliders[i], w->M_colliders[i - 1], left,
                              right, &collisionPoint)) {
        newPos.x = w->M_colliders[i].x;
        break;
      }
    }
    const Vector2 top{.x = newPos.x, .y = newPos.y - this->height};
    // Collision due to gravity
    for (size_t i = 1ull; i < w->M_colliders.size(); i++) {
      if (CheckCollisionLines(w->M_colliders[i], w->M_colliders[i - 1], newPos,
                              top, &collisionPoint)) {
        newPos.y = w->M_colliders[i].y;
        M_ground = true;
        break;
      }
    }
  } else {
    throw std::runtime_error("World was not set!");
  }

  M_position = newPos;

  if (M_velocity.y < cfg::TERMINAL) {
    M_velocity.y += cfg::GRAVITY * GetFrameTime();
  } else {
    M_velocity.y = cfg::TERMINAL;
  }

  if (M_velocity.x != 0.f) {
    M_state = State::MOVE;
  } else {
    M_state = State::STAND;
  }
}

void Entity::Render() { OnRender(); }