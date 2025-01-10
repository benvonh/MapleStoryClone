#include "world.hpp"

World::World()
  : music(LoadMusicStream("AboveTheTreetops.mp3")),
    platform(LoadTexture("lith_harbor.png")),
    background{},
    player(std::make_unique<Player>())
{
  if (!IsMusicValid(this->music))
    throw std::runtime_error("Music stream is not valid!");

  if (!IsTextureValid(this->platform))
    throw std::runtime_error("Platform texture is not valid!");

  // Image map = LoadImage("lith_harbor.png");
  // ImageResizeNN(&map, 1366, 768);
  // this->platform = LoadTextureFromImage(map);
  // UnloadImage(map);
  this->LoadBackground();
}

World::~World()
{
  UnloadMusicStream(this->music);
  UnloadTexture(this->platform);
  UnloadTexture(this->background);
}

void World::Create()
{
  PlayMusicStream(this->music);
  player->SetWorld(shared_from_this());
}

void World::Update()
{
  UpdateMusicStream(this->music);
  player->Update();

  if (IsWindowResized()) {
    this->LoadBackground();
  }
}

void World::Render()
{
  DrawTexture(this->background, 0, 0, WHITE);
  DrawTexture(this->platform, 0, 0, WHITE);
  player->Render();
}

void World::LoadBackground()
{
  Image image = LoadImage("background.png");

  if (!IsImageValid(image))
    throw std::runtime_error("Background image is not valid!");

  ImageResizeNN(&image, GetScreenWidth(), GetScreenHeight());
  this->background = LoadTextureFromImage(image);

  if (!IsTextureValid(this->background))
    throw std::runtime_error("Background texture is not valid!");

  UnloadImage(image);
}