#ifndef MAIN_MENU_STATE_HPP
#define MAIN_MENU_STATE_HPP

#include "engine/difficulty.hpp"
#include "engine/menu.hpp"
#include "engine/state.hpp"
#include "engine/stateManager.hpp"
#include "engine/window.hpp"

class MainMenuState : public State
{
  private:
    std::unique_ptr<Window> m_window{};
    Menu m_mainMenu{};
    Menu m_difficultyMenu{};
    bool m_difficultyMenuOpen{false};
    Difficulty m_difficulty{};

  public:
    MainMenuState(Difficulty difficulty = Difficulty::EASY);
    virtual ~MainMenuState();

    void handleInput(StateManager& manager, int input) override;
    void update(StateManager& manager) override;
    void render() override;

    void addMainMenuItems();
    void addDifficultyMenuItems();
};

#endif
