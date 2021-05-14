#include "cpputils/graphics/image_event.h"
#include "opponent.h"
#include "player.h"

#ifndef GAME_H
#define GAME_H
class Game : public graphics::AnimationEventListener,
             public graphics::MouseEventListener {
 public:
  Game() { game_screen_.Initialize(800, 600); }
  Game(int width, int height) { game_screen_.Initialize(width, height); }
  graphics::Image &GetGameScreen() { return game_screen_; }
  std::vector<std::unique_ptr<Opponent>> &GetOpponents() { return opponent_; }
  std::vector<std::unique_ptr<OpponentProjectile>> &GetOpponentProjectiles() {
    return opponentprojectile_;
  }
  std::vector<std::unique_ptr<PlayerProjectile>> &GetPlayerProjectiles() {
    return playerprojectile_;
  }
  Player &GetPlayer() { return player_; }
  void CreateOpponents();
  void CreateOpponentProjectiles();
  void CreatePlayerProjectiles();
  void Init();
  void UpdateScreen();
  void Start(graphics::Image &game) { game.ShowUntilClosed(); }
  void MoveGameElements();
  void FilterIntersections();
  void OnAnimationStep() override;
  void OnMouseEvent(const graphics::MouseEvent &mEvent) override;
  void LaunchProjectiles();
  void RemoveInactive();
  int GetScore();
  bool HasLost();

 private:
  graphics::Image game_screen_;
  std::vector<std::unique_ptr<Opponent>> opponent_;
  std::vector<std::unique_ptr<OpponentProjectile>> opponentprojectile_;
  std::vector<std::unique_ptr<PlayerProjectile>> playerprojectile_;
  Player player_;
  int game_score = 0;
  bool Lost = false;
};
#endif
