#include "world.hpp"
#include "raylib.h"
#include <fstream>
#include <sstream>
#include <stdexcept>

World::World() {
  if (!IsTextureValid(M__platform))
    throw std::runtime_error("Platform texture is invalid!");
}

World::~World() { UnloadTexture(M__platform); }

void World::Create() {
  M_player->world = shared_from_this();

  for (auto &m : M_monsters) {
    m.world = shared_from_this();
  }
}

void World::Update() {
  M_player->Update();

  M_camera.target.x = std::max(M_player->GetPosition().x,
                               static_cast<float>(GetScreenWidth()) / 2.f);

  M_camera.target.x =
      std::min(M_player->GetPosition().x,
               4690.f - static_cast<float>(GetScreenWidth()) / 2.f);

  M_camera.target.y =
      std::min(M_player->GetPosition().y,
               1590.f - static_cast<float>(GetScreenHeight()) / 2.f);

  if (IsWindowResized()) {
    M_camera.offset.x = static_cast<float>(GetScreenWidth()) / 2;
    M_camera.offset.y = static_cast<float>(GetScreenHeight()) / 2;
  }
}

void World::Render() {
  BeginMode2D(M_camera);
  DrawTexture(M__platform, 0, 0, WHITE);
  M_player->Render();
  EndMode2D();
}

std::vector<Vector2> World::load_colliders() {
  std::ifstream file("lith_harbor_colliders.txt");

  std::string line;
  std::vector<Vector2> colliders;

  while (std::getline(file, line)) {
    std::stringstream stream(line);

    char comma;
    float x, y;

    if (stream >> x >> comma >> y) {
      colliders.emplace_back(x, y);
    } else {
      throw std::runtime_error("Invalid collider file format!");
    }
  }
  return colliders;
}