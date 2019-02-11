#include "menuState.h"

MenuState::MenuState(StateStack& stack, Context context)
: State(stack, context)
{
    const std::string strs[] = {"Play Games", "Highscores", "Exit"};
    std::function<void()> funcs[] = {
        [this](){ requestStackPop(); requestStackPush(States::GameMenu); },
        [this](){ requestStackPop(); requestStackPush(States::Highscores); },
        [this](){ requestStackPop(); }
    };
    for(int i=0; i<3; i++)
    {
        std::unique_ptr<Button> button(new Button(context, strs[i], funcs[i], sf::Vector2f(400, 150 + 100*i)));
        mButtons.push_back(std::move(button));
    }
}

bool MenuState::handleEvent(sf::Event& event)
{
    for(auto it = mButtons.begin(); it != mButtons.end(); it++)
        (*it)->handleEvent(event);
    return true;
}

bool MenuState::update(sf::Time dt)
{
    for(auto it = mButtons.begin(); it != mButtons.end(); it++)
        (*it)->update();
    return true;
}

void MenuState::draw()
{
    //sf::RenderWindow& window = *getContext().window;

    for(auto it = mButtons.begin(); it != mButtons.end(); it++)
        (*it)->draw();
}
