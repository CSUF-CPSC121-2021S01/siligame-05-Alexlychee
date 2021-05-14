#include <iostream>
#include <string>

#include "cpputils/graphics/image.h"
#ifndef GAME_ElEMENT_H
#define GAME_ElEMENT_H
class GameElement {
 public:
  GameElement() : x_(0), y_(0), width_(50), height_(50) {}
  GameElement(int x, int y, int width, int height)
      : x_(x), y_(y), width_(width), height_(height), is_active_(true) {}
  int GetX() const { return x_; }
  int GetY() const { return y_; }
  int GetWidth() const { return width_; }
  int GetHeight() const { return height_; }
  bool GetIsActive() const { return is_active_; }
  void SetX(int x) { x_ = x; }
  void SetY(int y) { y_ = y; }
  void SetIsActive(bool is_active) { is_active_ = is_active; }
  virtual void Draw(graphics::Image &rectangle) = 0;
  virtual void Move(const graphics::Image &move) = 0;
  bool IntersectsWith(GameElement *game_element);
  bool IsOutOfBounds(const graphics::Image &bound);

 protected:
  int x_;
  int y_;
  int width_;
  int height_;
  bool is_active_;
};
#endif
