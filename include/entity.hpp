#pragma once
#include <cmath>
#include <string>
#include <memory>
#include "raylib.h"

// Declare to avoid
// circular dependency
class World;

class Entity
{
public:
  enum class Direction { UP, DOWN, LEFT, RIGHT };

  const std::string_view name = "";

  float speed = 0.f;

  Entity(const std::string &who, const std::string &texture);
  virtual ~Entity();
  virtual Vector2 GetPosition() const final;
  virtual Vector2 GetVelocity() const final;
  virtual void SetWorld(const std::shared_ptr<World> &ptr) final;
  virtual void Move(Direction direction) final;
  virtual void Update() final;
  virtual void Render() final;

protected:
  std::weak_ptr<World> world = {};

  virtual void OnUpdate() = 0;
  virtual void OnRender() = 0;

private:
  Vector2 M_position = {};
  Vector2 M_velocity = {};
  Texture M_texture = {};
};