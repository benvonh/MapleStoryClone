#include "entity.hpp"

Entity::Entity(const std::string &who, const std::string &texture)
  : name(who), speed(0.f), world{}, M_position{}, M_velocity{},
    M_texture(LoadTexture(texture.c_str()))
{
}

Entity::~Entity()
{
  UnloadTexture(M_texture);
}

Vector2 Entity::GetPosition() const
{
  return M_position;
}

Vector2 Entity::GetVelocity() const
{
  return M_velocity;
}

void Entity::SetWorld(const std::shared_ptr<World> &ptr)
{
  world = ptr;
}

void Entity::Move(Direction direction)
{
  switch (direction) {
  case Direction::UP:
    M_velocity.y = -speed;
    break;
  case Direction::DOWN:
    M_velocity.y = +speed;
    break;
  case Direction::LEFT:
    M_velocity.x = -speed;
    break;
  case Direction::RIGHT:
    M_velocity.x = +speed;
    break;
  }
}

void Entity::Update()
{
  OnUpdate();

  M_position.x += M_velocity.x * GetFrameTime();
  M_position.y += M_velocity.y * GetFrameTime();

  // if (M_velocity.x > 0) {
  //   M_velocity.x = std::max(0.f, M_velocity.x - speed / 2);
  // } else if (M_velocity.x < 0) {
  //   M_velocity.x = std::min(0.f, M_velocity.x + speed / 2);
  // }
  M_velocity.x = 0.f;

  if (M_velocity.y < 1000.f) {
    M_velocity.y += 1000.f * GetFrameTime();
  } else {
    M_velocity.y = 1000.f;
  }
}

void Entity::Render()
{
  OnRender();
  DrawTexture(M_texture, M_position.x, M_position.y, WHITE);
}