#include "engine/stateManager.hpp"
#include <chrono>
#include <ncurses.h>
#include <thread>

StateManager::StateManager() { m_states.reserve(3); }

void StateManager::pushState(std::unique_ptr<State> state)
{
    m_states.push_back(std::move(state));
}

void StateManager::popState(int count)
{
    for (int i{0}; i < count; ++i)
    {
        if (!m_states.empty())
            m_states.pop_back();
    }
}

State* StateManager::currentState() const
{
    return m_states.empty() ? nullptr : m_states.back().get();
}

void StateManager::handleInput(int input)
{
    currentState()->handleInput(*this, input);
}

void StateManager::update()
{
    if (auto* cs{currentState()})
        cs->update(*this);
}

void StateManager::render()
{
    if (auto* cs{currentState()})
        cs->render();
}

void StateManager::run()
{
    while (currentState())
    {
        int input{getch()};
        handleInput(input);
        update();
        render();
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
}
