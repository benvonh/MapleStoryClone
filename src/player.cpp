#include "player.hpp"
#include "raylib.h"

Player::Player() : Entity() {
  this->jump = 900.f;
  this->speed = 300.f;
  this->width = 43.f;
  this->height = 75.f;
}

void Player::OnUpdate() {
  if (IsKeyDown(KEY_SPACE)) {
    this->Move<Direction::JUMP>();
  }

  if (IsKeyDown(KEY_LEFT)) {
    this->Move<Direction::LEFT>();
  } else if (IsKeyDown(KEY_RIGHT)) {
    this->Move<Direction::RIGHT>();
  }
}

void Player::OnRender() {
  if (this->GetGround()) {
    if (this->GetState() == State::MOVE) {
      this->Animate(M_move);
    } else {
      this->Animate(M_stand);
    }
  } else {
    this->Animate(M_jump);
  }
}