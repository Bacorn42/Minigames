#include "pauseState.h"

PauseState::PauseState(StateStack& stack, Context context)
: State(stack, context)
, mBackGround(sf::Vector2f(250,130))
, mText("Paused", context.fonts->get(Fonts::Main), 24)
{
    const std::string strs[] = {"Resume"};
    std::function<void()> funcs[] = {
        [this](){ requestStackPop(); },
    };
    for(int i=0; i<1; i++)
    {
        std::unique_ptr<Button> button(new Button(context, strs[i], funcs[i], sf::Vector2f(300,325)));
        mButtons.push_back(std::move(button));
    }
    centerOrigin(mText);
    centerOrigin(mBackGround);
    mBackGround.setFillColor(sf::Color(96,96,96));
    mBackGround.setOutlineThickness(4);
    mBackGround.setOutlineColor(sf::Color(64,64,64));
    mBackGround.setPosition(sf::Vector2f(300,300));
    mText.setPosition(sf::Vector2f(300,265));
    mText.setColor(sf::Color::Black);
}

bool PauseState::handleEvent(sf::Event& event)
{
    for(auto it = mButtons.begin(); it != mButtons.end(); it++)
        (*it)->handleEvent(event);
    return false;
}

bool PauseState::update(sf::Time dt)
{
    for(auto it = mButtons.begin(); it != mButtons.end(); it++)
        (*it)->update();
    return false;
}

void PauseState::draw()
{
    sf::RenderWindow& window = *getContext().window;

    window.draw(mBackGround);
    window.draw(mText);
    for(auto it = mButtons.begin(); it != mButtons.end(); it++)
        (*it)->draw();
}
