#pragma once
#include "raylib.h"
#include "world.hpp"
#include <memory>
#include <stdexcept>

template <int W, int H> class Game final {
public:
  Game(const char *title) {
    SetConfigFlags(FLAG_VSYNC_HINT | FLAG_MSAA_4X_HINT | FLAG_WINDOW_RESIZABLE);
    InitWindow(W, H, title);

    if (!IsWindowReady())
      throw std::runtime_error("Window failed to initialize!");

    InitAudioDevice();

    if (!IsAudioDeviceReady())
      throw std::runtime_error("Audio device failed to initialize!");

    M_music = LoadMusicStream("AboveTheTreetops.mp3");

    if (!IsMusicValid(M_music))
      throw std::runtime_error("Music stream is not valid!");

    PlayMusicStream(M_music);
    reload_background();
    M_world = std::make_shared<World>();
  }

  ~Game() {
    UnloadTexture(M_background);
    UnloadMusicStream(M_music);
    CloseAudioDevice();
    CloseWindow();
  }

  void Loop() {
    M_world->Create();

    while (!WindowShouldClose()) {
      if (IsWindowResized()) {
        reload_background();
      }
      UpdateMusicStream(M_music);
      M_world->Update();

      BeginDrawing();
      ClearBackground(BLACK);
      DrawTexture(M_background, 0, 0, WHITE);
      M_world->Render();
      DrawFPS(0, 0);
      DrawText(TextFormat("HP: %u", M_world->GetPlayer()->GetHP()), 0,
               GetScreenHeight() - 48, 24, RED);
      DrawText(TextFormat("MP: %u", M_world->GetPlayer()->GetMP()), 0,
               GetScreenHeight() - 24, 24, BLUE);
      EndDrawing();
    }
  }

private:
  Music M_music{};
  Texture M_background{};
  std::shared_ptr<World> M_world = nullptr;

  void reload_background() {
    Image image = LoadImage("background.png");

    if (!IsImageValid(image))
      throw std::runtime_error("Background image is not valid!");

    ImageResizeNN(&image, GetScreenWidth(), GetScreenHeight());
    M_background = LoadTextureFromImage(image);

    if (!IsTextureValid(M_background))
      throw std::runtime_error("Invalid background texture!");

    UnloadImage(image);
  }
};