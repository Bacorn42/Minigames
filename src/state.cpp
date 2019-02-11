#include "state.h"
#include "statestack.h"

State::Context::Context(sf::RenderWindow& window, TextureHolder& textures, FontHolder& fonts, Highscore& highscores)
: window(&window)
, textures(&textures)
, fonts(&fonts)
, highscores(&highscores)
{

}

State::State(StateStack& stack, Context context)
: mStack(&stack)
, mContext(context)
{

}

void State::requestStackPush(States::ID ID)
{
    mStack->pushState(ID);
}

void State::requestStackPop()
{
    mStack->popState();
}

void State::requestStackClear()
{
    mStack->clearStates();
}

State::Context State::getContext()
{
    return mContext;
}
