#ifndef GAME_STATE_HPP
#define GAME_STATE_HPP

#include "engine/state.hpp"
#include "engine/stateManager.hpp"
#include <ncurses.h>

class GameState : public State
{
  private:
    WINDOW* m_window{nullptr};

  public:
    GameState();
    virtual ~GameState();

    void handleInput(StateManager& manager, int input) override;
    void update(StateManager& manager) override;
    void render() override;
};

#endif
