#ifndef MAIN_MENU_STATE_HPP
#define MAIN_MENU_STATE_HPP

#include "engine/state.hpp"
#include "engine/stateManager.hpp"
#include "engine/window.hpp"

class MainMenuState : public State
{
  private:
    std::unique_ptr<Window> m_window{};

  public:
    MainMenuState();
    virtual ~MainMenuState();

    void handleInput(StateManager& manager, int input) override;
    void update(StateManager& manager) override;
    void render() override;
};

#endif
