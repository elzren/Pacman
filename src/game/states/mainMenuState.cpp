#include "game/states/mainMenuState.hpp"
#include "game/states/gameState.hpp"

MainMenuState::MainMenuState()
{
    m_window = std::make_unique<Window>(0, 0, 0, 0);
    m_window->setTopLabel("Pacman");

    addMainMenuItems();
}

MainMenuState::~MainMenuState() {}

void MainMenuState::handleInput(StateManager& manager, int input)
{
    if (input == 'q')
        manager.popState();
    else if (input == '\n' && m_mainMenu.currentItem())
    {
        switch (m_mainMenu.currentItem()->id)
        {
        case MenuItem::START:
            manager.popState();
            manager.pushState(std::make_unique<GameState>());
            break;
        case MenuItem::EXIT:
            manager.popState();
            break;
        }
    }
    else
        m_mainMenu.handleInput(input);
}

void MainMenuState::update([[maybe_unused]] StateManager& manager) {}

void MainMenuState::render() { m_mainMenu.render(m_window.get()); }

void MainMenuState::addMainMenuItems()
{
    m_mainMenu.addItem(MenuItem{
        MenuItem::START,
        "Start",
    });
    m_mainMenu.addItem(MenuItem{
        MenuItem::EXIT,
        "Exit",
    });
}
