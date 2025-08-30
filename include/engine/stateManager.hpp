#ifndef STATE_MANAGER_HPP
#define STATE_MANAGER_HPP

#include "engine/state.hpp"
#include <memory>
#include <vector>

class StateManager
{
  private:
    std::vector<std::unique_ptr<State>> m_states{};

  public:
    StateManager();

    void pushState(std::unique_ptr<State> state);
    void popState();

    State* currentState() const;

    void handleInput(int input);
    void update();
    void render();

    void run();
};

#endif
