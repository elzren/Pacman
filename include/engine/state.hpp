#ifndef STATE_HPP
#define STATE_HPP

class StateManager;

class State
{
public:
    virtual ~State() = default;

    virtual void handleInput(StateManager& manager, int input) = 0;
    virtual void update(StateManager& manager) = 0;
    virtual void render() = 0;

    // virtual void onEnter() {};
    // virtual void onExit() {};
};

#endif
