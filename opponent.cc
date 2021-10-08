#include "opponent.h"

void Opponent::Draw(graphics::Image &my_opponent) {
  graphics::Image MONKEY;
  MONKEY.Load("opponent.bmp");
  for (int i = 0; i < MONKEY.GetHeight(); i++) {
    for (int j = 0; j < MONKEY.GetWidth(); j++) {
      my_opponent.SetColor(GetX() + j, GetY() + i, MONKEY.GetColor(j, i));
    }
  }
}

void Opponent::Move(const graphics::Image &move) {
  SetX(GetX() + 1);
  SetY(GetY() + 1);
  if (IsOutOfBounds(move)) {
    SetIsActive(false);
  }
}
std::unique_ptr<OpponentProjectile> Opponent::LaunchProjectile() {
  if (fire_rate >= 10) {
    fire_rate = 0;
    std::unique_ptr<OpponentProjectile> yellowfruit;
    yellowfruit = std::make_unique<OpponentProjectile>();
    return std::move(yellowfruit);
  } else {
    fire_rate++;
    return nullptr;
  }
}

void OpponentProjectile::Draw(graphics::Image &o_projectile) {
  graphics::Image BANANA;
  BANANA.Load("o_projectile.bmp");
  for (int i = 0; i < BANANA.GetHeight(); i++) {
    for (int j = 0; j < BANANA.GetWidth(); j++) {
      o_projectile.SetColor(GetX() + j, GetY() + i, BANANA.GetColor(j, i));
    }
  }
}
void OpponentProjectile::Move(const graphics::Image &move) {
  SetX(GetX() + 1);
  SetY(GetY() + 1);
  if (IsOutOfBounds(move)) {
    SetIsActive(false);
  }
}
