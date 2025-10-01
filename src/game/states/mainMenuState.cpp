#include "game/states/mainMenuState.hpp"
#include "engine/difficulty.hpp"
#include "engine/menuItem.hpp"
#include "game/states/gameState.hpp"

MainMenuState::MainMenuState(Difficulty difficulty) : m_difficulty{difficulty}
{
    m_window = std::make_unique<Window>(0, 0, 0, 0);
    m_window->setTopLabel("Pacman");

    addMainMenuItems();
    addDifficultyMenuItems();

    int terminalWidth, terminalHeight;
    getmaxyx(stdscr, terminalHeight, terminalWidth);

    m_menuWindow = std::make_unique<Window>(
        m_window.get(), m_menuWidth, m_mainMenu.itemsCount(),
        (terminalWidth - m_menuWidth) / 2,
        (terminalHeight - m_mainMenu.itemsCount()) / 2);
}

MainMenuState::~MainMenuState() {}

void MainMenuState::handleInput(StateManager& manager, int input)
{
    if (m_difficultyMenuOpen)
    {
        if (input == 27) // Esc
        {
            m_difficultyMenuOpen = false;
        }
        else if (input == '\n' && m_difficultyMenu.currentItem())
        {
            switch (m_difficultyMenu.currentItem()->id)
            {
            case MenuItem::EASY:
                m_difficulty = Difficulty::EASY;
                m_difficultyMenuOpen = false;
                break;
            case MenuItem::MEDIUM:
                m_difficulty = Difficulty::MEDIUM;
                m_difficultyMenuOpen = false;
                break;
            case MenuItem::HARD:
                m_difficulty = Difficulty::HARD;
                m_difficultyMenuOpen = false;
                break;
            default:
                break;
            }
        }
        else
            m_difficultyMenu.handleInput(input);
    }
    else
    {
        if (input == '\n' && m_mainMenu.currentItem())
        {
            switch (m_mainMenu.currentItem()->id)
            {
            case MenuItem::START:
                manager.popState();
                manager.pushState(std::make_unique<GameState>(m_difficulty));
                break;
            case MenuItem::EXIT:
                manager.popState();
                break;
            case MenuItem::DIFFICULTY:
                m_difficultyMenuOpen = true;
                break;
            default:
                break;
            }
        }
        else
            m_mainMenu.handleInput(input);
    }
}

void MainMenuState::update([[maybe_unused]] StateManager& manager) {}

void MainMenuState::render()
{
    m_window->erase();

    if (m_difficultyMenuOpen)
    {
        m_difficultyMenu.render(m_menuWindow.get(), 0, 0,
                                static_cast<int>(m_difficulty));
    }
    else
    {
        m_mainMenu.render(m_menuWindow.get(), 0, 0);
    }

    m_window->refresh();
}

void MainMenuState::addMainMenuItems()
{
    m_mainMenu.addItem(MenuItem{
        MenuItem::START,
        "Start",
    });
    m_mainMenu.addItem(MenuItem{
        MenuItem::DIFFICULTY,
        "Difficulty",
    });
    m_mainMenu.addItem(MenuItem{
        MenuItem::EXIT,
        "Exit",
    });
}

void MainMenuState::addDifficultyMenuItems()
{
    m_difficultyMenu.addItem(MenuItem{
        MenuItem::EASY,
        "Easy",
    });
    m_difficultyMenu.addItem(MenuItem{
        MenuItem::MEDIUM,
        "Medium",
    });
    m_difficultyMenu.addItem(MenuItem{
        MenuItem::HARD,
        "Hard",
    });
}
