#include "game.h"

void Game::Init() {
  game_screen_.AddMouseEventListener(*this);
  game_screen_.AddAnimationEventListener(*this);
  player_.SetX(10);
  player_.SetY(game_screen_.GetHeight() - 75);
}

void Game::CreateOpponents() {
  for (int i = 0; i < 5; i++) {
    opponent_.push_back(std::make_unique<Opponent>(50 * i + 15, 50));
  }
}
int Game::GetScore() { return game_score; }

bool Game::HasLost() { return Lost; }

void Game::UpdateScreen() {
  game_screen_.DrawRectangle(0, 0, 800, 600, 255, 255, 255);
  for (int i = 0; i < opponent_.size(); i++) {
    if (opponent_[i]->GetIsActive()) {
      opponent_[i]->Draw(game_screen_);
    }
  }
  for (int i = 0; i < opponentprojectile_.size(); i++) {
    if (opponentprojectile_[i]->GetIsActive()) {
      opponentprojectile_[i]->Draw(game_screen_);
    }
  }
  for (int i = 0; i < playerprojectile_.size(); i++) {
    if (playerprojectile_[i]->GetIsActive()) {
      playerprojectile_[i]->Draw(game_screen_);
    }
  }
  if (player_.GetIsActive()) {
    player_.Draw(game_screen_);
  }
  game_screen_.DrawText(10, 10, std::to_string(game_score), 35, 0, 0, 0);
}

void Game::MoveGameElements() {
  for (int i = 0; i < opponent_.size(); i++) {
    opponent_[i]->Move(game_screen_);
  }
  for (int j = 0; j < opponentprojectile_.size(); j++) {
    opponentprojectile_[j]->Move(game_screen_);
  }
  for (int h = 0; h < playerprojectile_.size(); h++) {
    playerprojectile_[h]->Move(game_screen_);
  }
}

void Game::FilterIntersections() {
  for (int i = 0; i < opponent_.size(); i++) {
    if (player_.IntersectsWith(opponent_[i].get()) == true) {
      player_.SetIsActive(false);
      opponent_[i]->SetIsActive(false);
      Lost = true;
    }
  }
  for (int i = 0; i < opponentprojectile_.size(); i++) {
    if (opponentprojectile_[i]->IntersectsWith(&player_) == true) {
      player_.SetIsActive(false);
      opponentprojectile_[i]->SetIsActive(false);
      Lost = true;
    }
  }
  for (int i = 0; i < playerprojectile_.size(); i++) {
    for (int j = 0; j < opponent_.size(); j++) {
      if (playerprojectile_[i]->IntersectsWith(opponent_[j].get()) == true) {
        playerprojectile_[i]->SetIsActive(false);
        opponent_[j]->SetIsActive(false);
        if (player_.GetIsActive() == true) {
          game_score++;
        }
      }
    }
  }
}

void Game::OnAnimationStep() {
  if (opponent_.size() == 0) {
    CreateOpponents();
  }
  MoveGameElements();
  LaunchProjectiles();
  FilterIntersections();
  RemoveInactive();
  UpdateScreen();
  game_screen_.Flush();
}

void Game::LaunchProjectiles() {
  for (int i = 0; i < opponent_.size(); i++) {
    if (opponent_[i]->LaunchProjectile() != nullptr) {
      std::unique_ptr<OpponentProjectile> fruit;
      fruit = std::make_unique<OpponentProjectile>();
      fruit->SetX(opponent_[i]->GetX());
      fruit->SetY(opponent_[i]->GetY());
      opponentprojectile_.push_back(std::move(fruit));
    }
  }
}

void Game::OnMouseEvent(const graphics::MouseEvent &mEvent) {
  if (mEvent.GetX() > 0 && mEvent.GetY() > 0 &&
      mEvent.GetX() < game_screen_.GetWidth() &&
      mEvent.GetY() < game_screen_.GetHeight()) {
    player_.SetX(mEvent.GetX() - 25);
    player_.SetY(mEvent.GetY() - 25);
  }
  if (mEvent.GetMouseAction() == graphics::MouseAction::kPressed) {
    std::unique_ptr<PlayerProjectile> shuriken =
        std::make_unique<PlayerProjectile>(mEvent.GetX(), mEvent.GetY() + 25);
    playerprojectile_.push_back(std::move(shuriken));
  }
  if (mEvent.GetMouseAction() == graphics::MouseAction::kDragged) {
    std::unique_ptr<PlayerProjectile> shuriken =
        std::make_unique<PlayerProjectile>(mEvent.GetX(), mEvent.GetY() + 25);
    playerprojectile_.push_back(std::move(shuriken));
  }
}

void Game::RemoveInactive() {
  for (int i = playerprojectile_.size() - 1; i >= 0; i--) {
    if (playerprojectile_[i]->GetIsActive() == false) {
      playerprojectile_.erase(playerprojectile_.begin() + i);
    }
  }
  for (int i = opponentprojectile_.size() - 1; i >= 0; i--) {
    if (opponentprojectile_[i]->GetIsActive() == false) {
      opponentprojectile_.erase(opponentprojectile_.begin() + i);
    }
  }
  for (int i = opponent_.size() - 1; i >= 0; i--) {
    if (!opponent_[i]->GetIsActive()) {
      opponent_.erase(opponent_.begin() + i);
    }
  }
}
