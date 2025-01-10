#include "player.hpp"

Player::Player() : Entity("player", "wabbit_alpha.png")
{
  this->speed = 400.f;
}

void Player::OnUpdate()
{
  if (IsKeyDown(KEY_SPACE)) {
    this->Move(Entity::Direction::UP);
  } else if (IsKeyDown(KEY_DOWN)) {
    this->Move(Entity::Direction::DOWN);
  }

  if (IsKeyDown(KEY_LEFT)) {
    this->Move(Entity::Direction::LEFT);
  } else if (IsKeyDown(KEY_RIGHT)) {
    this->Move(Entity::Direction::RIGHT);
  }

  if (IsKeyPressed(KEY_T)) {
  }
}

void Player::OnRender()
{
}