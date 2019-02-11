#include "gameMenuState.h"

GameMenuState::GameMenuState(StateStack& stack, Context context)
: State(stack, context)
{
    const std::string strs[] = {"Dodge", "Piano Hero"};
    std::function<void()> funcs[] = {
        [this](){ requestStackPop(); requestStackPush(States::DodgeGame); },
        [this](){ requestStackPop(); requestStackPush(States::PianoGame); }
    };
    for(int i=0; i<2; i++)
    {
        std::unique_ptr<Button> button(new Button(context, strs[i], funcs[i], sf::Vector2f(150, 100 + 75*i)));
        mButtons.push_back(std::move(button));
    }
    std::unique_ptr<Button> button(new Button(context, "Back", [this](){ requestStackPop(); requestStackPush(States::Menu); }, sf::Vector2f(150, 555)));
        mButtons.push_back(std::move(button));
}

bool GameMenuState::handleEvent(sf::Event& event)
{
    for(auto it = mButtons.begin(); it != mButtons.end(); it++)
        (*it)->handleEvent(event);
    return true;
}

bool GameMenuState::update(sf::Time dt)
{
    for(auto it = mButtons.begin(); it != mButtons.end(); it++)
        (*it)->update();
    return true;
}

void GameMenuState::draw()
{
    //sf::RenderWindow& window = *getContext().window;

    for(auto it = mButtons.begin(); it != mButtons.end(); it++)
        (*it)->draw();
}
