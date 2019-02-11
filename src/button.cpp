#include "button.h"

Button::Button(State::Context context, const std::string& str, std::function<void()> func, sf::Vector2f pos)
: mWindow(*context.window)
, mSprite(context.textures->get(Textures::MenuButtons), sf::IntRect(0,0,200,50))
, mText(str, context.fonts->get(Fonts::Main), 20)
, mFunction(func)
, currentState(Idle)
{
    centerOrigin(mSprite);
    centerOrigin(mText);
    mSprite.setPosition(pos);
    mText.setPosition(pos);
    mText.setColor(sf::Color::Black);
}

void Button::handleEvent(sf::Event& event)
{
    if(event.type == sf::Event::MouseButtonPressed)
        if(currentState == Hover)
            changeSprite(Pressed);
    if(event.type == sf::Event::MouseButtonReleased)
        if(currentState == Pressed)
        {
            changeSprite(Hover);
            mFunction();
        }
}

void Button::update()
{
    sf::IntRect rect(mSprite.getPosition().x-100, mSprite.getPosition().y-25, mSprite.getGlobalBounds().width, mSprite.getGlobalBounds().height);
    if(rect.contains(sf::Mouse::getPosition(mWindow)))
    {
        if(currentState == Idle)
            changeSprite(Hover);
    }
    else
        changeSprite(Idle);
}

void Button::draw()
{
    mWindow.draw(mSprite);
    mWindow.draw(mText);
}

void Button::changeSprite(Type type)
{
    mSprite.setTextureRect(sf::IntRect(0, 50*type, 200, 50));
    currentState = type;
}
