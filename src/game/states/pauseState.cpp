#include "game/states/pauseState.hpp"
#include "game/states/gameState.hpp"
#include "game/states/mainMenuState.hpp"

PauseState::PauseState()
{
    int terminalWidth, terminalHeight;
    getmaxyx(stdscr, terminalHeight, terminalWidth);

    m_window = std::make_unique<Window>(m_width, m_height,
                                        (terminalWidth - m_width) / 2,
                                        (terminalHeight - m_height) / 2);
    m_window->setTopLabel("Paused");

    addPauseMenuItems();
}

PauseState::~PauseState() {}

void PauseState::handleInput(StateManager& manager, int input)
{
    if (input == 27) // ESC key
    {
        manager.popState();
    }
    else if (input == '\n' && m_pauseMenu.currentItem())
    {
        switch (m_pauseMenu.currentItem()->id)
        {
        case MenuItem::RESUME:
            manager.popState();
            break;
        case MenuItem::RESTART:
            manager.popState(2);
            manager.pushState(std::make_unique<GameState>());
            break;
        case MenuItem::MAIN_MENU:
            manager.popState(2);
            manager.pushState(std::make_unique<MainMenuState>());
            break;
        case MenuItem::EXIT:
            manager.popState(2);
            break;
        default:
            break;
        }
    }
    else
        m_pauseMenu.handleInput(input);
}

void PauseState::update([[maybe_unused]] StateManager& manager) {}

void PauseState::render() { m_pauseMenu.render(m_window.get()); }

void PauseState::addPauseMenuItems()
{
    m_pauseMenu.addItem(MenuItem{
        MenuItem::RESUME,
        "Resume",
    });
    m_pauseMenu.addItem(MenuItem{
        MenuItem::RESTART,
        "Restart",
    });
    m_pauseMenu.addItem(MenuItem{
        MenuItem::MAIN_MENU,
        "Main Menu",
    });
    m_pauseMenu.addItem(MenuItem{
        MenuItem::EXIT,
        "Exit",
    });
}
