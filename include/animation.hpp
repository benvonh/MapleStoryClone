#pragma once
#include "raylib.h"
#include <array>
#include <format>
#include <stdexcept>

template <size_t N = 1ULL> class Animation final {
public:
  Animation(const std::array<const char *, N> &fileNames, double period)
      : C_period(period), C_textures(load_textures(fileNames)) {}

  ~Animation() {
    for (const auto &t : C_textures)
      UnloadTexture(t);
  }

  enum class Option { NONE, FLIP };

  template <Option O = Option::NONE> void Draw(const Vector2 &position) {
    if constexpr (N != 1) {
      const double time = GetTime();

      if (time - M_time > C_period) {
        M_time = time;
        M_frame = ++M_frame % C_textures.size();
      }
    }

    const Texture &texture = C_textures[M_frame];
    const int x = position.x - static_cast<float>(texture.width) / 2;
    const int y = position.y - static_cast<float>(texture.height);

    if constexpr (O == Option::FLIP) {
      const Rectangle source{.x = static_cast<float>(texture.width),
                             .y = 0.f,
                             .width = static_cast<float>(-texture.width),
                             .height = static_cast<float>(texture.height)};
      DrawTextureRec(texture, source,
                     {static_cast<float>(x), static_cast<float>(y)}, WHITE);
    } else {
      DrawTexture(texture, x, y, WHITE);
    }
  }

  bool Done() { return M_frame == 0; }

private:
  const double C_period;
  const std::array<Texture, N> C_textures;

  double M_time{GetTime()};
  size_t M_frame = 0ULL;

  static std::array<Texture, N>
  load_textures(const std::array<const char *, N> &fileNames) {
    std::array<Texture, N> textures;

    for (size_t i = 0; i < N; i++) {
      textures[i] = LoadTexture(fileNames[i]);

      if (!IsTextureValid(textures[i]))
        throw std::runtime_error(
            std::format("Invalid texture from {}", fileNames[i]));
    }

    return textures;
  }
};