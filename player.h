#include "opponent.h"
#ifndef PLAYER_H
#define PLAYER_H
class Player : public GameElement {
 public:
  Player() : Player(0, 0) {}
  Player(int x, int y) : GameElement(x, y, 50, 50) {}
  void Draw(graphics::Image &my_player);
  void Move(const graphics::Image &move);
};

class PlayerProjectile : public GameElement {
 public:
  PlayerProjectile() : PlayerProjectile(0, 0) {}
  PlayerProjectile(int x, int y) : GameElement(x, y, 25, 25) {}
  void Draw(graphics::Image &p_projectile);
  void Move(const graphics::Image &move);
};
#endif
