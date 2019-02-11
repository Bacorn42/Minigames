#ifndef HIGHSCORESTATE_H_INCLUDED
#define HIGHSCORESTATE_H_INCLUDED

#include <SFML/Graphics/Text.hpp>

#include "state.h"
#include "button.h"
#include "utilities.h"

#include <memory>

class HighscoreState : public State
{
    public:
        HighscoreState(StateStack& stack, Context context);
        virtual bool handleEvent(sf::Event& event);
        virtual bool update(sf::Time dt);
        virtual void draw();

    private:
        sf::Text mTexts[12];
        Button mButton;
};

#endif // HIGHSCORESTATE_H_INCLUDED
