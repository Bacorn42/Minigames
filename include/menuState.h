#ifndef MENUSTATE_H_INCLUDED
#define MENUSTATE_H_INCLUDED

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/RectangleShape.hpp>

#include "state.h"
#include "button.h"

#include <vector>
#include <string>
#include <memory>
#include <functional>

class MenuState : public State
{
    public:
        MenuState(StateStack& stack, Context context);
        virtual bool handleEvent(sf::Event& event);
        virtual bool update(sf::Time dt);
        virtual void draw();

    private:
        std::vector<std::unique_ptr<Button>> mButtons;
};

#endif // MENUSTATE_H_INCLUDED
