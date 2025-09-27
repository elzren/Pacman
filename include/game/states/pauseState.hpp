#ifndef PAUSE_STATE_HPP
#define PAUSE_STATE_HPP

#include "engine/menu.hpp"
#include "engine/state.hpp"
#include "engine/stateManager.hpp"
#include "engine/window.hpp"
#include <string_view>

class PauseState : public State
{
  private:
    std::unique_ptr<Window> m_window{};
    Menu m_pauseMenu{};
    int m_width{20};
    int m_height{};

  public:
    PauseState(bool resume = true, std::string_view label = "Paused");
    virtual ~PauseState();

    void handleInput(StateManager& manager, int input) override;
    void update(StateManager& manager) override;
    void render() override;

    void addPauseMenuItems(bool resume);
};

#endif
