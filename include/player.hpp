#pragma once
#include "raylib.h"
#include "entity.hpp"

class Player final : public Entity
{
public:
  Player();

protected:
  void OnUpdate() override;
  void OnRender() override;
};