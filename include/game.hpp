#pragma once
#include <memory>
#include <stdexcept>
#include "raylib.h"
#include "world.hpp"

template<int W, int H>
struct Game final
{
  Camera2D camera = {};
  std::shared_ptr<World> world = nullptr;

  Game(const char *title) : camera{}, world(nullptr)
  {
    SetConfigFlags(FLAG_VSYNC_HINT | FLAG_MSAA_4X_HINT | FLAG_WINDOW_RESIZABLE);
    InitWindow(W, H, title);
    InitAudioDevice();

    if (!IsWindowReady())
      throw std::runtime_error("Window failed to initialize!");

    if (!IsAudioDeviceReady())
      throw std::runtime_error("Audio device failed to initialize!");
    
    // OpenGL context before world
    this->world = std::make_shared<World>();
  }

  ~Game()
  {
    CloseAudioDevice();
    CloseWindow();
  }

  void Loop()
  {
    this->world->Create();

    while (!WindowShouldClose()) {
      this->world->Update();

      this->camera.zoom = 1.f;
      this->camera.target = this->world->player->GetPosition();
      std::printf("'' %.2f, %.2f\n", this->camera.target.x, this->camera.target.y);
      this->camera.offset = Vector2{W / 2, H / 2};

      BeginDrawing();
      ClearBackground(BLACK);
      BeginMode2D(this->camera);
      this->world->Render();
      EndMode2D();
      DrawFPS(0, 0);
      EndDrawing();
    }
  }
};