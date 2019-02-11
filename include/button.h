#ifndef BUTTON_H_INCLUDED
#define BUTTON_H_INCLUDED

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>

#include "utilities.h"
#include "state.h"
#include "resourceHolder.h"
#include "resourceIdentifiers.h"

#include <functional>
#include <string>

class Button
{
    public:
        enum Type
        {
            Idle,
            Hover,
            Pressed
        };
        Button(State::Context Context, const std::string& str, std::function<void()> func, sf::Vector2f pos);
        void handleEvent(sf::Event& event);
        void update();
        void draw();
        void changeSprite(Type type);

    private:
        sf::RenderWindow& mWindow;
        sf::Sprite mSprite;
        sf::Text mText;
        std::function<void()> mFunction;
        Type currentState;
};

#endif // BUTTON_H_INCLUDED
