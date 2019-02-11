#ifndef PAUSESTATE_H_INCLUDED
#define PAUSESTATE_H_INCLUDED

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Text.hpp>

#include "state.h"
#include "button.h"

#include <vector>
#include <string>
#include <memory>
#include <functional>

class PauseState : public State
{
    public:
        PauseState(StateStack& stack, Context context);
        virtual bool handleEvent(sf::Event& event);
        virtual bool update(sf::Time dt);
        virtual void draw();

    private:
        std::vector<std::unique_ptr<Button>> mButtons;
        sf::RectangleShape mBackGround;
        sf::Text mText;
};

#endif // PAUSESTATE_H_INCLUDED
