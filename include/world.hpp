#pragma once
#include "monster.hpp"
#include "player.hpp"
#include "raylib.h"
#include "raymath.h"
#include <memory>
#include <vector>

class World final : public std::enable_shared_from_this<World> {
  friend Entity;

public:
  World();
  ~World();
  void Create();
  void Update();
  void Render();
  const std::unique_ptr<Player> &GetPlayer() const noexcept { return M_player; }

private:
  const Texture M__platform = LoadTexture("lith_harbor.png");

  Camera2D M_camera{.offset = {static_cast<float>(GetScreenWidth()) / 2,
                               static_cast<float>(GetScreenHeight()) / 2},
                    .target = Vector2Zero(),
                    .rotation = 0.f,
                    .zoom = 1.f};
  std::vector<Monster> M_monsters{Monster()};
  std::vector<Vector2> M_colliders = load_colliders();
  std::unique_ptr<Player> M_player = std::make_unique<Player>();

  static std::vector<Vector2> load_colliders();
};