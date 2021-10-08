#include "game.h"
int main() {
  Game game;
  game.Init();
  game.Start(game.GetGameScreen());
  return 0;
}
