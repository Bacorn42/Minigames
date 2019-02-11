#include "highscoreState.h"

HighscoreState::HighscoreState(StateStack& stack, Context context)
: State(stack, context)
, mButton(context, "Back", [this](){ requestStackPop(); requestStackPush(States::Menu); }, sf::Vector2f(150, 555))
{
    for(int i=0; i<12; i++)
    {
        mTexts[i].setFont(getContext().fonts->get(Fonts::Main));
        mTexts[i].setCharacterSize(24);
        mTexts[i].setColor(sf::Color::White);
    }
    mTexts[0].setString("Dodge:");
    mTexts[0].setPosition(sf::Vector2f(32,0));
     mTexts[1].setString("Piano Hero:");
     mTexts[1].setPosition(sf::Vector2f(432,0));
    mTexts[2].setString("Seconds survived:");
    mTexts[2].setPosition(sf::Vector2f(32,64));
     mTexts[3].setString("Score:");
     mTexts[3].setPosition(sf::Vector2f(32,184));
    mTexts[4].setString("Seconds survived:");
    mTexts[4].setPosition(sf::Vector2f(432,64));
     mTexts[5].setString("Combo:");
     mTexts[5].setPosition(sf::Vector2f(432,184));
    mTexts[6].setString("Score:");
    mTexts[6].setPosition(sf::Vector2f(432,304));
     mTexts[7].setString(toString(getContext().highscores->getScore<float>(Highscore::DodgeSeconds)));
     mTexts[7].setPosition(sf::Vector2f(32,104));
    mTexts[8].setString(toString(getContext().highscores->getScore<int>(Highscore::DodgeScore)));
    mTexts[8].setPosition(sf::Vector2f(32,224));
     mTexts[9].setString(toString(getContext().highscores->getScore<float>(Highscore::PianoSeconds)));
     mTexts[9].setPosition(sf::Vector2f(432,104));
    mTexts[10].setString(toString(getContext().highscores->getScore<int>(Highscore::PianoCombo)));
    mTexts[10].setPosition(sf::Vector2f(432,224));
     mTexts[11].setString(toString(getContext().highscores->getScore<int>(Highscore::PianoScore)));
     mTexts[11].setPosition(sf::Vector2f(432,344));
}

bool HighscoreState::handleEvent(sf::Event& event)
{
    mButton.handleEvent(event);
    return true;
}

bool HighscoreState::update(sf::Time dt)
{
    mButton.update();
    return true;
}

void HighscoreState::draw()
{
    sf::RenderWindow& window = *getContext().window;
    mButton.draw();
    for(int i=0; i<12; i++)
        window.draw(mTexts[i]);
}
