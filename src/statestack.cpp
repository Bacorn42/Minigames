#include "statestack.h"

StateStack::PendingChange::PendingChange(Action action, States::ID ID)
: action(action)
, ID(ID)
{

}

StateStack::StateStack(State::Context context)
: mContext(context)
, mStack()
, mPendingChanges()
, mStates()
{

}

void StateStack::handleEvent(sf::Event& event)
{
    for(auto it = mStack.rbegin(); it != mStack.rend(); it++)
        if(!(*it)->handleEvent(event))
            break;
}

void StateStack::update(sf::Time dt)
{
    for(auto it = mStack.rbegin(); it != mStack.rend(); it++)
        if(!(*it)->update(dt))
            break;

    applyPendingChanges();
}

void StateStack::draw()
{
    for(auto it = mStack.begin(); it != mStack.end(); it++)
        (*it)->draw();
}

void StateStack::pushState(States::ID ID)
{
    mPendingChanges.push_back(PendingChange(Push, ID));
}

void StateStack::popState()
{
    mPendingChanges.push_back(PendingChange(Pop));
}

void StateStack::clearStates()
{
    mPendingChanges.push_back(PendingChange(Clear));
}

bool StateStack::isEmpty()
{
    return mStack.empty();
}

State::Ptr StateStack::createState(States::ID ID)
{
    auto found = mStates.find(ID);
    return found->second();
}

void StateStack::applyPendingChanges()
{
    for(auto it = mPendingChanges.begin(); it != mPendingChanges.end(); it++)
    {
        if((*it).action == Push)
            mStack.push_back(createState((*it).ID));
        else if((*it).action == Pop)
            mStack.pop_back();
        else if((*it).action == Clear)
            mStack.clear();
    }
    mPendingChanges.clear();
}
