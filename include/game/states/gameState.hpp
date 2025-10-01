#ifndef GAME_STATE_HPP
#define GAME_STATE_HPP

#include "engine/difficulty.hpp"
#include "engine/state.hpp"
#include "engine/stateManager.hpp"
#include "engine/window.hpp"
#include "game/board.hpp"
#include "game/ghostManager.hpp"
#include "game/player.hpp"
#include <memory>

class GameState : public State
{
  private:
    std::unique_ptr<Window> m_window{};
    std::unique_ptr<Window> m_gameWindow{};
    Difficulty m_difficulty{};
    Board m_board{};
    Player m_player{};
    GhostManager m_ghostManager{m_difficulty};
    int m_level{1};
    int frameCount{};

  public:
    GameState(Difficulty difficulty);
    virtual ~GameState();

    void initializeBoard();
    void initializePlayer();
    void restart();
    int frameDelay() const;
    void incrementFrameCount();

    void handleInput(StateManager& manager, int input) override;
    void update(StateManager& manager) override;
    void render() override;
};

#endif
