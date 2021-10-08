#include "player.h"

void Player::Draw(graphics::Image &my_player) {
  graphics::Image NINJA;
  NINJA.Load("player.bmp");
  for (int i = 0; i < NINJA.GetHeight(); i++) {
    for (int j = 0; j < NINJA.GetWidth(); j++) {
      my_player.SetColor(GetX() + j, GetY() + i, NINJA.GetColor(j, i));
    }
  }
}
void Player::Move(const graphics::Image &move) {}

void PlayerProjectile::Draw(graphics::Image &p_projectile) {
  graphics::Image STAR;
  STAR.Load("p_projectile.bmp");
  for (int i = 0; i < STAR.GetHeight(); i++) {
    for (int j = 0; j < STAR.GetWidth(); j++) {
      p_projectile.SetColor(GetX() + j, GetY() + i, STAR.GetColor(j, i));
    }
  }
}

void PlayerProjectile::Move(const graphics::Image &move) {
  SetY(GetY() - 8);
  if (IsOutOfBounds(move)) {
    SetIsActive(false);
  }
}
