#ifndef GAME_STATE_HPP
#define GAME_STATE_HPP

#include "engine/state.hpp"
#include "engine/stateManager.hpp"
#include "engine/window.hpp"

class GameState : public State
{
  private:
    std::unique_ptr<Window> m_window{};

  public:
    GameState();
    virtual ~GameState();

    void handleInput(StateManager& manager, int input) override;
    void update(StateManager& manager) override;
    void render() override;
};

#endif
