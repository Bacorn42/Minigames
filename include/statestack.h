#ifndef STATESTACK_H_INCLUDED
#define STATESTACK_H_INCLUDED

#include "state.h"

#include <vector>
#include <map>
#include <functional>

class StateStack
{
    public:
        enum Action
        {
            Push,
            Pop,
            Clear
        };

        StateStack(State::Context context);
        void handleEvent(sf::Event& event);
        void update(sf::Time dt);
        void draw();
        void pushState(States::ID ID);
        void popState();
        void clearStates();
        bool isEmpty();

        template<typename T>
        void registerState(States::ID ID);

    private:
        State::Ptr createState(States::ID ID);
        void applyPendingChanges();

        struct PendingChange
        {
            PendingChange(Action action, States::ID ID = States::None);
            Action action;
            States::ID ID;
        };

        State::Context mContext;
        std::vector<State::Ptr> mStack;
        std::vector<PendingChange> mPendingChanges;
        std::map<States::ID, std::function<State::Ptr()>> mStates;
};

template<typename T>
void StateStack::registerState(States::ID ID)
{
    mStates[ID] = [this]()
    {
        return State::Ptr(new T(*this, mContext));
    };
}

#endif // STATESTACK_H_INCLUDED
