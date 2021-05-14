#include "game_element.h"
bool GameElement::IntersectsWith(GameElement *game_element) {
  return !(GetX() > game_element->GetX() + game_element->GetWidth() ||
           game_element->GetX() > GetX() + GetWidth() ||
           GetY() > game_element->GetY() + game_element->GetHeight() ||
           game_element->GetY() > GetY() + GetHeight());
}
bool GameElement::IsOutOfBounds(const graphics::Image &bound) {
  if (x_ + width_ > bound.GetWidth() || y_ + height_ > bound.GetHeight() ||
      x_ < 0 || y_ < 0) {
    return true;
  } else {
    return false;
  }
}
