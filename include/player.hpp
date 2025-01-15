#pragma once
#include "animation.hpp"
#include "config.hpp"
#include "entity.hpp"
#include <array>

class Player final : public Entity {
public:
  Player();

protected:
  void OnUpdate() override;
  void OnRender() override;

private:
  static constexpr std::array KANNA_DIE = {
      "kanna/die1_0.png",  "kanna/die1_1.png",  "kanna/die1_2.png",
      "kanna/die1_3.png",  "kanna/die1_4.png",  "kanna/die1_5.png",
      "kanna/die1_6.png",  "kanna/die1_7.png",  "kanna/die1_8.png",
      "kanna/die1_9.png",  "kanna/die1_10.png", "kanna/die1_11.png",
      "kanna/die1_12.png", "kanna/die1_13.png"};
  static constexpr std::array KANNA_MOVE = {
      "kanna/move_0.png", "kanna/move_1.png", "kanna/move_2.png",
      "kanna/move_3.png"};
  static constexpr std::array KANNA_STAND = {
      "kanna/stand_0.png", "kanna/stand_1.png", "kanna/stand_2.png",
      "kanna/stand_3.png"};
  static constexpr std::array KANNA_ATTACK1 = {
      "kanna/attack1_0.png", "kanna/attack1_1.png", "kanna/attack1_2.png",
      "kanna/attack1_3.png", "kanna/attack1_4.png", "kanna/attack1_5.png",
      "kanna/attack1_6.png", "kanna/attack1_7.png", "kanna/attack1_8.png",
      "kanna/attack1_9.png", "kanna/attack1_10.png"};
  static constexpr std::array KANNA_ATTACK2 = {
      "kanna/attack2_0.png",  "kanna/attack2_1.png",  "kanna/attack2_2.png",
      "kanna/attack2_3.png",  "kanna/attack2_4.png",  "kanna/attack2_5.png",
      "kanna/attack2_6.png",  "kanna/attack2_7.png",  "kanna/attack2_8.png",
      "kanna/attack2_9.png",  "kanna/attack2_10.png", "kanna/attack2_11.png",
      "kanna/attack2_12.png", "kanna/attack2_13.png", "kanna/attack2_14.png",
      "kanna/attack2_15.png", "kanna/attack2_16.png", "kanna/attack2_17.png",
      "kanna/attack2_18.png", "kanna/attack2_19.png", "kanna/attack2_20.png",
      "kanna/attack2_21.png", "kanna/attack2_22.png", "kanna/attack2_23.png",
      "kanna/attack2_24.png", "kanna/attack2_25.png"};
  static constexpr std::array KANNA_ATTACK3 = {
      "kanna/attack3_0.png",  "kanna/attack3_1.png",  "kanna/attack3_2.png",
      "kanna/attack3_3.png",  "kanna/attack3_4.png",  "kanna/attack3_5.png",
      "kanna/attack3_6.png",  "kanna/attack3_7.png",  "kanna/attack3_8.png",
      "kanna/attack3_9.png",  "kanna/attack3_10.png", "kanna/attack3_11.png",
      "kanna/attack3_12.png", "kanna/attack3_13.png", "kanna/attack3_14.png"};

  Animation<> M_hit{{"kanna/hit1_0.png"}, 0};
  Animation<> M_jump{{"kanna/jump_0.png"}, 0};
  Animation<KANNA_DIE.size()> M_die{KANNA_DIE, cfg::DIE_TIME};
  Animation<KANNA_MOVE.size()> M_move{KANNA_MOVE, cfg::MOVE_TIME};
  Animation<KANNA_STAND.size()> M_stand{KANNA_STAND, cfg::STAND_TIME};
  Animation<KANNA_ATTACK1.size()> M_attack1{KANNA_ATTACK1, cfg::ATTACK_TIME};
  Animation<KANNA_ATTACK2.size()> M_attack2{KANNA_ATTACK2, cfg::ATTACK_TIME};
  Animation<KANNA_ATTACK3.size()> M_attack3{KANNA_ATTACK3, cfg::ATTACK_TIME};
};