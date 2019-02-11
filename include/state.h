#ifndef STATE_H_INCLUDED
#define STATE_H_INCLUDED

#include <SFML/System/Time.hpp>

#include "stateIdentifiers.h"
#include "resourceIdentifiers.h"
#include "highscore.h"

#include <memory>

namespace sf
{
    class RenderWindow;
    class Event;
    class Time;
}

class StateStack;

class State
{
    public:
        typedef std::unique_ptr<State> Ptr;

        struct Context
        {
            Context(sf::RenderWindow& window, TextureHolder& textures, FontHolder& fonts, Highscore& highscores);
            sf::RenderWindow* window;
            TextureHolder* textures;
            FontHolder* fonts;
            Highscore* highscores;
        };

        State(StateStack& stack, Context context);
        virtual bool handleEvent(sf::Event& event) = 0;
        virtual bool update(sf::Time dt) = 0;
        virtual void draw() = 0;

    protected:
        void requestStackPush(States::ID ID);
        void requestStackPop();
        void requestStackClear();
        Context getContext();

    private:
        StateStack* mStack;
        Context mContext;
};

#endif // STATE_H_INCLUDED
