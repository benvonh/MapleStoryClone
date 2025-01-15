#pragma once
#include "entity.hpp"

class Monster final : public Entity
{
public:
  Monster();

protected:
  void OnUpdate() override;
  void OnRender() override;
};