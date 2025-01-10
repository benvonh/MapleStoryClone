#pragma once
#include <memory>
#include <stdexcept>
#include "raylib.h"
#include "player.hpp"

class World final : public std::enable_shared_from_this<World>
{
public:
  Music music = {};
  Texture platform = {};
  Texture background = {};
  std::unique_ptr<Player> player = nullptr;

  World();
  ~World();
  void Create();
  void Update();
  void Render();

private:
  void LoadBackground();
};